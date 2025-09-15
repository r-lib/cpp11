test_that("cpp_source local controls RTTI/vtable symbol visibility", {
  skip_on_os("windows")

  mk_dirs <- function() {
    d1 <- tempfile("cpp_source_local1")
    d2 <- tempfile("cpp_source_local2")
    dir.create(d1); dir.create(d2)
    list(provider = d1, consumer = d2)
  }

  unload_dirs <- function(dirs) {
    dlls <- getLoadedDLLs()
    for (nm in names(dlls)) {
      # Some R builds/platforms expose different DLL info; access $path
      # defensively to avoid errors when the structure differs (macOS).
      p <- tryCatch({ dlls[[nm]]$path }, error = function(e) NULL)
      if (!is.null(p)) {
        for (d in dirs) {
          if (grepl(d, p, fixed = TRUE)) {
            tryCatch(dyn.unload(p), error = function(e) NULL)
          }
        }
      }
    }
  }

  provider_so_path <- function(dir) {
    src <- file.path(dir, "src")
    files <- list.files(src, pattern = paste0("\\\\", .Platform$dynlib.ext, "$"), ignore.case = TRUE)
    if (length(files) == 0) return(character())
    file.path(src, files[[1]])
  }

  dirs <- mk_dirs()
  on.exit({
    unload_dirs(unlist(dirs))
    unlink(unlist(dirs), recursive = TRUE, force = TRUE)
  }, add = TRUE)

  # Provider: abstract Base + Impl factory (polymorphic triggers RTTI/vtable)
  provider_code <- '
    #include <cpp11/R.hpp>
    struct Base { virtual ~Base(){}; virtual int foo() = 0; };
    struct Impl : Base { int foo() override { return 77; } };

    extern "C" Base* make_impl() { return new Impl(); }
    extern "C" void destroy_impl(Base* p) { delete p; }
  '

  # Consumer uses typeid(Base) (forces reference to typeinfo symbol) and
  # calls the factory produced by the provider.
  consumer_code <- '\n#include <cpp11/R.hpp>\n#include <typeinfo>\n#include <string>\nstruct Base { virtual ~Base(){}; virtual int foo() = 0; };\nextern "C" Base* make_impl();\nextern "C" SEXP call_typeinfo_and_run() {\n  const std::type_info& t = typeid(Base);\n  std::string n = t.name();\n  Base* b = make_impl();\n  int v = b->foo();\n  delete b;\n  SEXP out = PROTECT(Rf_allocVector(INTSXP, 2));\n  INTEGER(out)[0] = (int)n.size();\n  INTEGER(out)[1] = v;\n  UNPROTECT(1);\n  return out;\n}\n'

  # 1) provider loaded with local = TRUE -> consumer should fail to load
  expect_silent(cpp_source(code = provider_code, dir = dirs$provider, clean = FALSE, local = TRUE))
  expect_error(
    cpp_source(code = consumer_code, dir = dirs$consumer, clean = FALSE),
    regexp = "undefined symbol|symbol .* not found|undefined reference|symbol not found in flat namespace",
    ignore.case = TRUE
  )

  # Clean up partial loads
  unload_dirs(unlist(dirs))

  # 2) provider loaded with local = FALSE -> consumer loads and runs
  expect_silent(cpp_source(code = provider_code, dir = dirs$provider, clean = FALSE, local = FALSE))
  expect_silent(cpp_source(code = consumer_code, dir = dirs$consumer, clean = FALSE))

  res <- .Call("call_typeinfo_and_run")
  expect_true(is.integer(res) && length(res) == 2)
  expect_equal(as.integer(res)[2], 77L)
  expect_true(as.integer(res)[1] > 0)

  # Explicit check that the manual dyn.load(...) workaround is unnecessary.
  # Emulate the snippet to locate the provider shared object and show that it
  # exists; we already demonstrated the consumer works without running this
  # manual snippet because cpp_source(local = FALSE) provided global symbols.
  so_path <- provider_so_path(dirs$provider)
  expect_true(file.exists(so_path))
  # Loading it manually with local = FALSE would succeed, but wasn't required.
  expect_silent(dyn.load(so_path, local = FALSE, now = TRUE))
})
