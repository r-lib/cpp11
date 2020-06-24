#' Compile C++ code
#'
#' [cpp_source()] compiles and loads a single C++ file for use in R.
#' [cpp_function()] compiles and loads a single function for use in R.
#' [cpp_eval()] evaluates a single C++ expression and returns the result.
#'
#' @param file A file containing C++ code to compile
#' @param code If non-null, the C++ code to compile
#' @param env The R environment where the R wrapping functions should be defined.
#' @param clean If `TRUE`, cleanup the files after sourcing
#' @param quiet If 'TRUE`, do not show compiler output
#' @return For [cpp_source()] and `[cpp_function()]` the results of
#'   [dyn.load()] (invisibly). For `[cpp_eval()]` the results of the evaluated
#'   expression.
#' @examples
#' \dontrun{
#' cpp_source(
#'   code = '#include "cpp11/integers.hpp"
#'
#'   [[cpp11::export]]
#'   int num_odd(cpp11::integers x) {
#'     int total = 0;
#'     for (int val : x) {
#'       if ((val % 2) == 1) {
#'         ++total;
#'       }
#'     }
#'     return total;
#'   }
#'   ')
#'
#' num_odd(as.integer(c(1:10, 15, 23)))
#' }
#' @export
cpp_source <- function(file, code = NULL, env = parent.frame(), clean = TRUE, quiet = TRUE) {
  dir <- tempfile()
  dir.create(dir)
  dir.create(file.path(dir, "R"))
  dir.create(file.path(dir, "src"))

  if (!is.null(code)) {
    file <- file.path(dir, "src", sprintf("code_%s.cpp", the$count))
    writeLines(code, file)
    the$count <- the$count + 1L
  } else {
    if (!any(tools::file_ext(file) %in% c("cpp", "cc"))) {
      stop("`file` must have a `.cpp` or `.cc` extension")
    }
    file.copy(file, file.path(dir, "src", basename(file)))
    file <- file.path(dir, "src", basename(file))
  }

  package <- tools::file_path_sans_ext(basename(file))

  suppressWarnings(
    all_decorations <- decor::cpp_decorations(dir, is_attribute = TRUE)
  )
  cli_suppress(
    exports <- get_exported_functions(all_decorations, "cpp11")
  )
  cpp_functions_definitions <- generate_cpp_functions(exports, package = package)

  exports_file <- file.path(dir, "src", "cpp11-exports.cpp")
  writeLines(c('#include "cpp11/declarations.hpp"', "using namespace cpp11;", cpp_functions_definitions), exports_file)

  includes <- generate_include_paths("cpp11")

  if (isTRUE(clean)) {
    on.exit(unlink(dir, recursive = TRUE))
  }

  r_functions <- generate_r_functions(exports, package = package, use_package = TRUE)

  makevars_content <- generate_makevars(includes)

  writeLines(makevars_content, file.path(dir, "src", "Makevars"))

  source_files <- normalizePath(c(file, exports_file), winslash = "/")
  callr::rcmd("SHLIB", source_files, user_profile = TRUE, show = !quiet, wd = file.path(dir, "src"))

  shared_lib <- file.path(dir, "src", paste0(tools::file_path_sans_ext(basename(file)), .Platform$dynlib.ext))

  r_exports <- file.path(dir, "R", "cpp11-exports.R")
  writeLines(r_functions, r_exports)
  source(r_exports, local = env)

  dyn.load(shared_lib, local = TRUE, now = TRUE)
}

the <- new.env(parent = emptyenv())
the$count <- 0L

generate_include_paths <- function(packages) {
  out <- character(length(packages))
  for (i in seq_along(packages)) {
    out[[i]] <- paste0("-I", system.file(package = packages[[i]], "include"))
  }
  out
}

generate_makevars <- function(includes) {
  c("CXX_STD=CXX11", sprintf("PKG_CPPFLAGS=%s", paste0(includes, collapse = " ")))
}

#' @rdname cpp_source
#' @export
cpp_function <- function(code, env = parent.frame(), clean = TRUE, quiet = TRUE) {
  cpp_source(code = paste(c('#include "cpp11.hpp"', "using namespace cpp11;", "namespace writable = cpp11::writable;", "[[cpp11::export]]", code), collapse = "\n"), env = env, clean = clean, quiet = quiet)
}

utils::globalVariables("f")

#' @rdname cpp_source
#' @export
cpp_eval <- function(code) {
  cpp_source(code = paste(c('#include "cpp11.hpp"', "using namespace cpp11;", "namespace writable = cpp11::writable;", "[[cpp11::export]]", "SEXP f() { return as_sexp(", code, ");", "}"), collapse = "\n"), env = environment())
  f()
}
