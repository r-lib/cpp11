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
#' cpp11` from your DESCRIPTION. This is done automatically by this function.
#'
#' **Note**: vendoring places the responsibility of updating the code on
#' **you**. Bugfixes and new features in cpp11 will not be available for your
#' code until you run `cpp_vendor()` again.
#'
#' @param path The path to vendor the code into. The default is
#'  `./inst/include/`.
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
cpp_vendor <- function(path = "./inst/include/") {
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

  message(sprintf(
    "Adding PKG_CPPFLAGS = -I../%s to src/Makevars and src/Makevars.win.",
    new
  ))

  makevars <- "src/Makevars"
  makevars_win <- "src/Makevars.win"
  makevars_line <- paste0("PKG_CPPFLAGS = -I ../", new)

  if (file.exists(makevars)) {
    if (!any(grepl(paste0("^PKG_CPPFLAGS\\s*=\\s*-I\\s*\\.\\./", new), readLines(makevars)))) {
      writeLines(c(readLines(makevars), makevars_line), makevars)
    }
  } else {
    writeLines(makevars_line, makevars)
  }

  if (file.exists(makevars_win)) {
    if (!any(grepl(paste0("^PKG_CPPFLAGS\\s*=\\s*-I\\s*\\.\\./", new), readLines(makevars_win)))) {
      writeLines(c(readLines(makevars_win), makevars_line), makevars_win)
    }
  } else {
    writeLines(makevars_line, makevars_win)
  }

  message("Removing 'LinkingTo: cpp11' from DESCRIPTION.")

  desc <- readLines("DESCRIPTION")
  desc <- desc[!grepl("^LinkingTo:\\s*cpp11", desc)]
  desc <- gsub("^LinkingTo:\\s*cpp11,\\s*", "LinkingTo: ", desc)
  desc <- gsub(",\\s*cpp11", "", desc)

  writeLines(descr, "DESCRIPTION")

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
