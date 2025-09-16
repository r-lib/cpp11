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
#' code until you run `cpp_vendor()` again.
#'
#' @inheritParams cpp_register
#' @param headers The path to the cpp11 headers to vendor. By default this is
#'  the path where R installed the cpp11 package. You can change this to
#'  use a different version of cpp11, such as as the development version
#'  from GitHub. 
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
cpp_vendor <- function(path = ".", headers = system.file("include", "cpp11", package = "cpp11")) {
  new <- file.path(path, "inst", "include", "cpp11")

  if (dir.exists(new)) {
    message("'", new, "' already exists, removing it")
    cpp_unvendor(path)
  }

  dir.create(new , recursive = TRUE, showWarnings = FALSE)

  if (!nzchar(headers)) {
    stop("cpp11 is not installed", call. = FALSE)
  }

  cpp11_version <- utils::packageVersion("cpp11")

  cpp11_header <- sprintf("// cpp11 version: %s\n// vendored on: %s", cpp11_version, Sys.Date())

  files <- list.files(headers, full.names = TRUE)

  writeLines(
    c(cpp11_header, readLines(system.file("include", "cpp11.hpp", package = "cpp11"))),
    file.path(dirname(new), "cpp11.hpp")
  )

  for (f in files) {
    writeLines(c(cpp11_header, readLines(f)), file.path(new, basename(f)))
  }

  invisible(new)
}
