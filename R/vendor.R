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
#' @param path The path to vendor the code into.
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
cpp_vendor <- function(path = NULL) {
  if (is.null(path)) {
    stop("You must provide a path to vendor the code into", call. = FALSE)
  } else {
    path <- paste0(path, "/inst/include")
  }
  
  new <- file.path(path)

  if (dir.exists(new)) {
    stop("'", new, "' already exists\n * run unlink('", new, "', recursive = TRUE)", call. = FALSE)
  }

  # Vendor cpp11 ----

  dir.create(new, recursive = TRUE, showWarnings = FALSE)
  dir.create(file.path(new, "cpp11"), recursive = TRUE, showWarnings = FALSE)

  current <- system.file("include", "cpp11", package = "cpp11")

  if (!nzchar(current)) {
    stop("cpp11 is not installed", call. = FALSE)
  }

  cpp11_version <- utils::packageVersion("cpp11")

  cpp11_header <- sprintf("// cpp11 version: %s\n// vendored on: %s", cpp11_version, Sys.Date())

  main_header <- list.files(current, pattern = "\\.hpp$", full.names = TRUE)
  headers <- list.files(file.path(current, "cpp11"), pattern = "\\.hpp$", full.names = TRUE)

  writeLines(c(cpp11_header, readLines(main_header)), file.path(new, basename(main_header)))

  for (h in headers) {
    writeLines(c(cpp11_header, readLines(h)), file.path(new, "cpp11", basename(h)))
  }

  # Additional steps to make vendoring work ----

  message(paste(
    "Makevars and/or Makevars.win should have a line such as",
    "'PKG_CPPFLAGS = -I../inst/include'"
  ))

  message("DESCRIPTION should not have lines such as 'LinkingTo: cpp11'")

  invisible(new)
}

write_header <- function(path, header, pkg, cpp11_header) {
  writeLines(
    c(
      cpp11_header,
      readLines(system.file("include", header, package = pkg))
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
