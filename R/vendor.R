#' Vendor the cpp11 dependency
#'
#' Vendoring is the act of making your own copy of the 3rd party packages your
#' project is using. It is often used in the go language community.
#'
#' This function vendors cpp11 into your package by copying the cpp11
#' headers into the `inst/include` folder of your package and adding
#' 'cpp11 version: XYZ' to the top of the files, where XYZ is the version of
#' cpp11 currently installed on your machine.
#'
#' If you choose to vendor the headers you should _remove_ `LinkingTo:
#' cpp11` from your DESCRIPTION.
#'
#' **Note**: vendoring places the responsibility of updating the code on
#' **you**. Bugfixes and new features in cpp11 will not be available for your
#' code until you run `vector_cpp11()` again.
#'
#' @inheritParams cpp_register
#' @return The file path to the vendored code (invisibly).
#' @export
#' @examples
#' # create a new directory
#' dir <- tempfile()
#' dir.create(dir)
#'
#' # vendor the cpp11 headers into the directory
#' cpp_vendor(dir)
#'
#' list.files(file.path(dir, "inst", "include", "cpp11"))
#'
#' # cleanup
#' unlink(dir, recursive = TRUE)
cpp_vendor <- function(path = ".") {
  new <- file.path(path, "inst", "include", "cpp11")

  if (dir.exists(new)) {
    stop("'", new, "' already exists\n * run unlink('", new, "', recursive = TRUE)", call. = FALSE)
  }

  dir.create(new , recursive = TRUE, showWarnings = FALSE)

  current <- system.file("include", "cpp11", package = "cpp11")
  if (!nzchar(current)) {
    stop("cpp11 is not installed", call. = FALSE)
  }

  cpp11_version <- utils::packageVersion("cpp11")

  cpp11_header <- sprintf("// cpp11 version: %s\n// vendored on: %s", cpp11_version, Sys.Date())

  files <- list.files(current, full.names = TRUE)

  writeLines(
    c(cpp11_header, readLines(system.file("include", "cpp11.hpp", package = "cpp11"))),
    file.path(dirname(new), "cpp11.hpp")
  )

  for (f in files) {
    writeLines(c(cpp11_header, readLines(f)), file.path(new, basename(f)))
  }

  invisible(new)
}
