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
#' @inheritParams generate_exports
#' @export
vendor_cpp11 <- function(path = ".") {
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

  for (f in list.files(current, full.names = TRUE)) {
    writeLines(c(cpp11_header, readLines(f)), file.path(new, basename(f)))
  }

  invisible(new)
}
