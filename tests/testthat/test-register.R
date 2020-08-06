describe("pkg_links_to_rcpp", {
  it("works with single package in LinkingTo", {
    pkg <- local_package()

    expect_false(pkg_links_to_rcpp(pkg_path(pkg)))

    pkg$set("LinkingTo", "Rcpp")
    pkg$write()

    expect_true(pkg_links_to_rcpp(pkg_path(pkg)))
  })

  it("works with multiple packages in LinkingTo", {
    pkg <- local_package()

    expect_false(pkg_links_to_rcpp(pkg_path(pkg)))

    pkg$set("LinkingTo", paste("Rcpp", "cpp11", sep = ","))
    pkg$write()

    expect_true(pkg_links_to_rcpp(pkg_path(pkg)))
  })
})

describe("get_call_entries", {
  it("returns an empty string if there are no R files", {
    pkg <- local_package()
    expect_equal(get_call_entries(pkg_path(pkg)), "")
  })

  it("returns an empty string if there are no .Call calls", {
    pkg <- local_package()
    dir.create(file.path(pkg_path(pkg), "R"))
    writeLines("foo <- function() 1", file.path(pkg_path(pkg), "R", "foo.R"))
    expect_equal(get_call_entries(pkg_path(pkg)), "")
  })

  it("returns an empty string for packages without NAMESPACE files", {
    # local_package adds a NAMESPACE file
    pkg <- tempfile()
    dir.create(pkg)
    on.exit(unlink(pkg, recursive = TRUE))

    writeLines("Package: testPkg", file.path(pkg, "DESCRIPTION"))
    dir.create(file.path(pkg, "R"))
    writeLines('foo <- function() .Call("bar")', file.path(pkg, "R", "foo.R"))
    expect_equal(get_call_entries(pkg), "")
  })

  it("returns an empty string for packages with .Call entries and NAMESPACE files", {

    # tools::package_native_routine_registration_skeleton is not available before R 3.4
    skip_if(getRversion() < "3.4")

    pkg <- local_package()
    dir.create(file.path(pkg_path(pkg), "R"))
    writeLines('foo <- function() .Call("bar")', file.path(pkg_path(pkg), "R", "foo.R"))
    expect_equal(
      get_call_entries(pkg_path(pkg)),
      c("/* .Call calls */",
        "extern SEXP bar();",
        "",
        "static const R_CallMethodDef CallEntries[] = {",
        "    {\"bar\", (DL_FUNC) &bar, 0},",
        "    {NULL, NULL, 0}",
        "};"
      )
    )
  })
})

describe("wrap_call", {
  it("works with void functions and no arguments", {
    expect_equal(
      wrap_call("foo", "void", tibble::tibble(type = character(), name = character())),
      "  foo();\n    return R_NilValue;"
    )
  })
  it("works with non-void functions and no arguments", {
    expect_equal(
      wrap_call("foo", "bool", tibble::tibble(type = character(), name = character())),
      "  return cpp11::as_sexp(foo());"
    )
  })
  it("works with void functions and some arguments", {
    expect_equal(
      wrap_call("foo", "void", tibble::tibble(type = c("double", "int"), name = c("x", "y"))),
      "  foo(cpp11::as_cpp<cpp11::decay_t<double>>(x), cpp11::as_cpp<cpp11::decay_t<int>>(y));\n    return R_NilValue;"
    )
  })
  it("works with non-void functions and some arguments", {
    expect_equal(
      wrap_call("foo", "bool", tibble::tibble(type = c("double", "int"), name = c("x", "y"))),
      "  return cpp11::as_sexp(foo(cpp11::as_cpp<cpp11::decay_t<double>>(x), cpp11::as_cpp<cpp11::decay_t<int>>(y)));"
    )
  })
})

describe("get_registered_functions", {
  it("returns an empty tibble given a non-existent file", {
    f <- tempfile()
    decorations <- decor::cpp_decorations(files = f, is_attribute = TRUE)
    res <- get_registered_functions(decorations, "cpp11::register")
    expect_equal(names(res), c("file", "line", "decoration", "params", "context", "name", "return_type", "args"))
    expect_equal(NROW(res), 0)
  })

  it("returns an empty tibble given a empty file", {
    f <- tempfile()
    file.create(f)
    decorations <- decor::cpp_decorations(files = f, is_attribute = TRUE)
    res <- get_registered_functions(decorations, "cpp11::register")
    expect_equal(names(res), c("file", "line", "decoration", "params", "context", "name", "return_type", "args"))
    expect_equal(NROW(res), 0)
  })

  it("works with a single registration", {
    decorations <- decor::cpp_decorations(files = test_path("single.cpp"), is_attribute = TRUE)
    res <- get_registered_functions(decorations, "cpp11::register")
    expect_equal(names(res), c("file", "line", "decoration", "params", "context", "name", "return_type", "args"))
    expect_equal(NROW(res), 1L)
    expect_equal(res$name, "foo")
    expect_equal(res$return_type, "int")
    expect_equal(names(res$args[[1]]), c("type", "name", "default"))
    expect_equal(NROW(res$args[[1]]), 0)
  })

  it("works with multiple registrations", {
    decorations <- decor::cpp_decorations(files = test_path("multiple.cpp"), is_attribute = TRUE)
    res <- get_registered_functions(decorations, "cpp11::register")
    expect_equal(names(res), c("file", "line", "decoration", "params", "context", "name", "return_type", "args"))
    expect_equal(NROW(res), 3L)
    expect_equal(res$name, c("foo", "bar", "baz"))
    expect_equal(res$return_type, c("int", "double", "bool"))
    expect_equal(names(res$args[[1]]), c("type", "name", "default"))
    expect_equal(NROW(res$args[[1]]), 0)

    expect_equal(names(res$args[[2]]), c("type", "name", "default"))
    expect_equal(NROW(res$args[[2]]), 1)
    expect_equal(res$args[[2]]$type, "bool")
    expect_equal(res$args[[2]]$name, "run")
    expect_equal(res$args[[2]]$default, NA_character_)

    expect_equal(names(res$args[[3]]), c("type", "name", "default"))
    expect_equal(NROW(res$args[[3]]), 2)
    expect_equal(res$args[[3]]$type, c("bool", "int"))
    expect_equal(res$args[[3]]$name, c("run", "value"))
    expect_equal(res$args[[3]]$default, c(NA_character_, "0"))
  })
})

describe("generate_cpp_functions", {
  it("returns the empty string if there are no functions", {
    funs <- tibble::tibble(
      file = character(),
      line = integer(),
      decoration = character(),
      params = list(),
      context = list(),
      name = character(),
      return_type = character(),
      args = list(tibble::tibble(type = character(), name = character()))
    )

    expect_equal(generate_cpp_functions(funs), character())
  })

  it("returns the wrapped function for a single void function with no arguments", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "void",
      args = list(tibble::tibble(type = character(), name = character()))
    )

    expect_equal(generate_cpp_functions(funs),
"// foo.cpp
void foo();
extern \"C\" SEXP _cpp11_foo() {
  BEGIN_CPP11
    foo();
    return R_NilValue;
  END_CPP11
}"
    )
  })

  it("returns the wrapped function for a single void function with no arguments and different package name", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "void",
      args = list(tibble::tibble(type = character(), name = character()))
    )

    expect_equal(generate_cpp_functions(funs, package = "mypkg"),
"// foo.cpp
void foo();
extern \"C\" SEXP _mypkg_foo() {
  BEGIN_CPP11
    foo();
    return R_NilValue;
  END_CPP11
}"
    )
  })


  it("returns the wrapped function for a single function with no arguments", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "int",
      args = list(tibble::tibble(type = character(), name = character()))
    )

    expect_equal(generate_cpp_functions(funs),
"// foo.cpp
int foo();
extern \"C\" SEXP _cpp11_foo() {
  BEGIN_CPP11
    return cpp11::as_sexp(foo());
  END_CPP11
}"
    )
  })

  it("returns the wrapped function for a single void function with arguments", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "void",
      args = list(tibble::tibble(type = "int", name = "bar"))
    )

    expect_equal(generate_cpp_functions(funs),
"// foo.cpp
void foo(int bar);
extern \"C\" SEXP _cpp11_foo(SEXP bar) {
  BEGIN_CPP11
    foo(cpp11::as_cpp<cpp11::decay_t<int>>(bar));
    return R_NilValue;
  END_CPP11
}"
    )
  })

  it("returns the wrapped function for a single function with arguments", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "int",
      args = list(tibble::tibble(type = "int", name = "bar"))
    )

    expect_equal(generate_cpp_functions(funs),
"// foo.cpp
int foo(int bar);
extern \"C\" SEXP _cpp11_foo(SEXP bar) {
  BEGIN_CPP11
    return cpp11::as_sexp(foo(cpp11::as_cpp<cpp11::decay_t<int>>(bar)));
  END_CPP11
}"
    )
  })

  it("returns the wrapped functions for multiple functions with arguments", {
    funs <- tibble::tibble(
      file = c("foo.cpp", "bar.cpp"),
      line = c(1L, 3L),
      decoration = c("cpp11", "cpp11"),
      params = list(NA, NA),
      context = list(NA_character_, NA_character_),
      name = c("foo", "bar"),
      return_type = c("int", "bool"),
      args = list(
        tibble::tibble(type = "int", name = "bar"),
        tibble::tibble(type = "double", name = "baz")
      )
    )

    expect_equal(generate_cpp_functions(funs),
"// foo.cpp
int foo(int bar);
extern \"C\" SEXP _cpp11_foo(SEXP bar) {
  BEGIN_CPP11
    return cpp11::as_sexp(foo(cpp11::as_cpp<cpp11::decay_t<int>>(bar)));
  END_CPP11
}
// bar.cpp
bool bar(double baz);
extern \"C\" SEXP _cpp11_bar(SEXP baz) {
  BEGIN_CPP11
    return cpp11::as_sexp(bar(cpp11::as_cpp<cpp11::decay_t<double>>(baz)));
  END_CPP11
}"
    )
  })
})

describe("generate_r_functions", {
  it("returns the empty string if there are no functions", {
    funs <- tibble::tibble(
      file = character(),
      line = integer(),
      decoration = character(),
      params = list(),
      context = list(),
      name = character(),
      return_type = character(),
      args = list()
    )

    expect_equal(generate_r_functions(funs), character())
  })

  it("returns the wrapped function for a single void function with no arguments", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "void",
      args = list(tibble::tibble(type = character(), name = character()))
    )

    expect_equal(generate_r_functions(funs, package = "cpp11"),
"foo <- function() {
  invisible(.Call(\"_cpp11_foo\"))
}")
  })

  it("returns the wrapped function for a single void function with no arguments and use_package = TRUE", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "void",
      args = list(tibble::tibble(type = character(), name = character()))
    )

    expect_equal(generate_r_functions(funs, package = "cpp11", use_package = TRUE),
"foo <- function() {
  invisible(.Call(\"_cpp11_foo\", PACKAGE = \"cpp11\"))
}")
  })

  it("returns the wrapped function for a single void function with no arguments and different package name", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "void",
      args = list(tibble::tibble(type = character(), name = character()))
    )

    expect_equal(generate_r_functions(funs, package = "mypkg"),
"foo <- function() {
  invisible(.Call(\"_mypkg_foo\"))
}")
  })

  it("returns the wrapped function for a single function with no arguments", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "int",
      args = list(tibble::tibble(type = character(), name = character()))
    )

    expect_equal(generate_r_functions(funs, package = "cpp11"),
"foo <- function() {
  .Call(\"_cpp11_foo\")
}")
  })

  it("returns the wrapped function for a single function with no arguments and use_package = TRUE", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "int",
      args = list(tibble::tibble(type = character(), name = character()))
    )

    expect_equal(generate_r_functions(funs, package = "cpp11", use_package = TRUE),
"foo <- function() {
  .Call(\"_cpp11_foo\", PACKAGE = \"cpp11\")
}")
  })

  it("returns the wrapped function for a single void function with arguments", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "void",
      args = list(tibble::tibble(type = "int", name = "bar"))
    )

    expect_equal(generate_r_functions(funs, package = "cpp11"),
"foo <- function(bar) {
  invisible(.Call(\"_cpp11_foo\", bar))
}")
  })

  it("returns the wrapped function for a single function with arguments", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "int",
      args = list(tibble::tibble(type = "int", name = "bar"))
    )

    expect_equal(generate_r_functions(funs, package = "cpp11"),
"foo <- function(bar) {
  .Call(\"_cpp11_foo\", bar)
}")
  })

  it("returns the wrapped functions for multiple functions with arguments", {
    funs <- tibble::tibble(
      file = c("foo.cpp", "bar.cpp"),
      line = c(1L, 3L),
      decoration = c("cpp11", "cpp11"),
      params = list(NA, NA),
      context = list(NA_character_, NA_character_),
      name = c("foo", "bar"),
      return_type = c("int", "bool"),
      args = list(
        tibble::tibble(type = "int", name = "bar"),
        tibble::tibble(type = "double", name = "baz")
      )
    )

    expect_equal(generate_r_functions(funs, package = "cpp11"),
"foo <- function(bar) {
  .Call(\"_cpp11_foo\", bar)
}

bar <- function(baz) {
  .Call(\"_cpp11_bar\", baz)
}")
  })
})

describe("cpp_register", {
  it("returns an invisible empty character if there are no decorations", {
    f <- tempfile()
    expect_equal(cpp_register(f), character())

    dir.create(f)
    expect_equal(cpp_register(f), character())

  })
  it("works with a package that registers a single c++ function", {

    # tools::package_native_routine_registration_skeleton is not available before R 3.4
    skip_if(getRversion() < "3.4")

    pkg <- local_package()
    p <- pkg_path(pkg)
    dir.create(file.path(p, "src"))
    file.copy(test_path("single.cpp"), file.path(p, "src", "single.cpp"))
    cpp_register(p)

    r_bindings <- file.path(p, "R", "cpp11.R")
    expect_true(file.exists(r_bindings))
    expect_equal(read_file(r_bindings),
"# Generated by cpp11: do not edit by hand

foo <- function() {
  .Call(\"_testPkg_foo\")
}
")
    cpp_bindings <- file.path(p, "src", "cpp11.cpp")
    expect_true(file.exists(cpp_bindings))
    expect_equal(read_file(cpp_bindings),
"// Generated by cpp11: do not edit by hand
// clang-format off


#include \"cpp11/declarations.hpp\"

// single.cpp
int foo();
extern \"C\" SEXP _testPkg_foo() {
  BEGIN_CPP11
    return cpp11::as_sexp(foo());
  END_CPP11
}

extern \"C\" {
/* .Call calls */
extern SEXP _testPkg_foo();

static const R_CallMethodDef CallEntries[] = {
    {\"_testPkg_foo\", (DL_FUNC) &_testPkg_foo, 0},
    {NULL, NULL, 0}
};
}

extern \"C\" void R_init_testPkg(DllInfo* dll){
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
")
  })

  it("can be run without messages", {
    pkg <- local_package()
    p <- pkg_path(pkg)
    dir.create(file.path(p, "src"))
    file.copy(test_path("single.cpp"), file.path(p, "src", "single.cpp"))
    expect_silent(cpp_register(p, quiet = TRUE))
  })


  it("can be run with messages, by default", {
    pkg <- local_package()
    p <- pkg_path(pkg)
    dir.create(file.path(p, "src"))
    file.copy(test_path("single.cpp"), file.path(p, "src", "single.cpp"))
    expect_message(cpp_register(p), "1 functions decorated with [[cpp11::register]]", fixed = TRUE)
  })

  it("includes pkg_types.h if included in src", {
    pkg <- local_package()
    p <- pkg_path(pkg)
    dir.create(file.path(p, "src"))
    file.copy(test_path("single.cpp"), file.path(p, "src", "single.cpp"))
    writeLines("#include <sstream>", file.path(p, "src", "testPkg_types.h"))
    cpp_register(p)

    expect_true(
      any(
        grepl(
          pattern = '#include "testPkg_types.h"',
          x = readLines(file.path(p, "src", "cpp11.cpp")),
          fixed = TRUE
        )
      )
    )
  })

  it("includes pkg_types.h if included in inst/include", {
    pkg <- local_package()
    p <- pkg_path(pkg)
    dir.create(file.path(p, "src"))
    file.copy(test_path("single.cpp"), file.path(p, "src", "single.cpp"))

    dir.create(file.path(p, "inst", "include"), recursive = TRUE)
    writeLines("#include <sstream>", file.path(p, "inst", "include", "testPkg_types.h"))
    cpp_register(p)

    expect_true(
      any(
        grepl(
          pattern = '#include "testPkg_types.h"',
          x = readLines(file.path(p, "src", "cpp11.cpp")),
          fixed = TRUE
        )
      )
    )
  })

  it("does not error if no files have registered functions", {
    pkg <- local_package()
    p <- pkg_path(pkg)
    dir.create(file.path(p, "src"))
    writeLines("int foo(int x) { return x; }", file.path(p, "src", "foo.cpp"))

    expect_error_free(cpp_register(p))
  })
})

describe("generate_init_functions", {
  it("returns an empty list if there no functions", {
    funs <- tibble::tibble(
      file = character(),
      line = integer(),
      decoration = character(),
      params = list(),
      context = list(),
      name = character(),
      return_type = character(),
      args = list(tibble::tibble(type = character(), name = character()))
    )

    expect_equal(generate_init_functions(funs), list(declarations = "", calls = ""))
  })

  it("returns the declaration and call for a single init function", {
    funs <- tibble::tibble(
      file = "foo.cpp",
      line = 1L,
      decoration = "cpp11",
      params = list(NA),
      context = list(NA_character_),
      name = "foo",
      return_type = "void",
      args = list(tibble::tibble(type = "DllInfo*", name = "dll"))
    )

    expect_equal(generate_init_functions(funs), list(declarations = "\nvoid foo(DllInfo* dll);\n", calls = "\n  foo(dll);"))
  })

  it("returns the declaration and call for a multiple init functions", {
    funs <- tibble::tibble(
      file = c("foo.cpp", "bar.cpp"),
      line = c(1L, 3L),
      decoration = c("cpp11", "cpp11"),
      params = list(NA, NA),
      context = list(NA_character_, NA_character_),
      name = c("foo", "bar"),
      return_type = c("void", "void"),
      args = list(tibble::tibble(type = "DllInfo*", name = "dll"), tibble::tibble(type = "DllInfo*", name = "dll"))
    )

    expect_equal(generate_init_functions(funs), list(declarations = "\nvoid foo(DllInfo* dll);\nvoid bar(DllInfo* dll);\n", calls = "\n  foo(dll);\n  bar(dll);"))
  })
})
