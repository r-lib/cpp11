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
#' **Note**: vendoring places the responsibility of updating the code on
#' **you**. Bugfixes and new features in cpp11 will not be available for your
#' code until you run `cpp_vendor()` again.
#'
#' @inheritParams cpp_register
#' @param dir The directoyy to vendor the code into.
#' @param subdir The subdirectory to vendor the code into.
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
cpp_vendor <- function(dir = NULL, subdir = "/inst/include") {
  if (is.null(dir)) {
    stop("You must provide a path to vendor the code into", call. = FALSE)
  }

  path <- paste0(dir, subdir)

  path2 <- file.path(path, "cpp11")
  if (dir.exists(path2)) {
    stop("'", path2, "' already exists\n * run unlink('", path2, "', recursive = TRUE)", call. = FALSE)
  }

  # Vendor cpp11 ----

  dir.create(
    path2,
    recursive = TRUE,
    showWarnings = FALSE
  )

  current_cpp11 <- system.file(
    "include",
    "cpp11",
    package = "cpp11"
  )

  if (!nzchar(current_cpp11)) {
    stop("cpp11 is not installed", call. = FALSE)
  }

  cpp11_version <- utils::packageVersion("cpp11")

  cpp11_header <- sprintf(
    "// cpp11 version: %s\n// vendored on: %s",
    cpp11_version,
    Sys.Date()
  )

  write_header(
    path, "cpp11.hpp", "cpp11",
    cpp11_header
  )

  copy_files(
    list.files(current_cpp11, full.names = TRUE),
    path, "cpp11", cpp11_header
  )

  # Additional steps to make vendoring work ----

  message(paste(
    "Makevars and/or Makevars.win should have a line such as",
    "'PKG_CPPFLAGS = -I../inst/include'"
  ))

  message("DESCRIPTION should not have lines such as 'LinkingTo: cpp11'")

  files <- list.files(headers, full.names = TRUE)

  invisible(path)
}

write_header <- function(path, header, pkg, cpp11armadillo_header) {
  writeLines(
    c(
      cpp11armadillo_header,
      readLines(
        system.file("include", header, package = pkg)
      )
    ),
    file.path(path, header)
  )
}

copy_files <- function(files, path, out, cpp11armadillo_header) {
  for (f in files) {
    writeLines(
      c(cpp11armadillo_header, readLines(f)),
      file.path(path, out, basename(f))
    )
  }
}
