#' Vendor the cpp11 dependency
#'
#' Vendoring is the act of making your own copy of the 3rd party packages your
#' project is using. It is often used in the go language community.
#'
#' This function vendors cpp11 into your package by copying the cpp11
#' headers into the `src/vendor` folder and adding 'cpp11 version: XYZ' to the
#' top of the files, where XYZ is the version of cpp11 currently installed on
#' your machine.
#'
#' If you choose to vendor the headers you should _remove_ `LinkingTo:
#' cpp11` from your DESCRIPTION. This is done automatically by this function.
#'
#' **Note**: vendoring places the responsibility of updating the code on
#' **you**. Bugfixes and new features in cpp11 will not be available for your
#' code until you run `cpp_vendor()` again.
#'
#' @param path The path to vendor the code into. The default is `./inst/include/`.
#' @return The file path to the vendored code (invisibly).
#' @export
#' @examples
#' # create a new directory
#' dir <- tempdir()
#' dir.create(dir)
#'
#' # vendor the cpp11 headers into the directory
#' cpp_vendor(dir)
#'
#' # cleanup
#' unlink(dir, recursive = TRUE)
cpp_vendor <- function(path = "./inst/include") {
  new <- file.path(path, "cpp11")

  if (dir.exists(new)) {
    stop("'", new, "' already exists\n * run unlink('", new, "', recursive = TRUE)", call. = FALSE)
  }

  # Vendor cpp11 ----

  dir.create(
    new,
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

  invisible(path)
}

write_header <- function(path, header, pkg, cpp11_header) {
  writeLines(
    c(
      cpp11_header,
      readLines(
        system.file("include", header, package = pkg)
      )
    ),
    file.path(path, header)
  )
}

copy_files <- function(files, path, out, cpp11_header) {
  for (f in files) {
    writeLines(
      c(cpp11_header, readLines(f)),
      file.path(path, out, basename(f))
    )
  }
}
