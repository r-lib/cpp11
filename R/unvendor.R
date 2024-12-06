#' Unvendor the cpp11 dependency
#'
#' This function removes the vendored cpp11 headers from your package and
#' restores the `LinkingTo: cpp11` field in the DESCRIPTION file if it was removed.
#'
#' @inheritParams cpp_register
#' @return The file path to the unvendored code (invisibly).
#' @export
#' @examples
#' # create a new directory
#' dir <- tempfile()
#' dir.create(dir)
#'
#' # vendor the cpp11 headers into the directory
#' cpp_vendor(dir)
#'
#' # unvendor the cpp11 headers from the directory
#' unvendor_cpp11(dir)
#'
#' list.files(file.path(dir, "inst", "include", "cpp11"))
#'
#' # cleanup
#' unlink(dir, recursive = TRUE)
cpp_unvendor <- function(path = ".") {
  new <- file.path(path, "inst", "include", "cpp11")

  if (!dir.exists(new)) {
    stop("'", new, "' does not exist", call. = FALSE)
  }

  unlink(new, recursive = TRUE)

  cpp11_hpp <- file.path(dirname(new), "cpp11.hpp")
  if (file.exists(cpp11_hpp)) {
    unlink(cpp11_hpp)
  }

  invisible(new)
}
