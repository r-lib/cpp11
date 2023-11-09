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
#' list.files(file.path(dir, "src", "vendor"))
#'
#' # cleanup
#' unlink(dir, recursive = TRUE)
cpp_vendor <- function(path = "./src/vendor") {
  new <- file.path(path, "cpp11")

  if (dir.exists(new)) {
    stop("'", new, "' already exists\n * run unlink('", new, "', recursive = TRUE)", call. = FALSE)
  }

  dir.create(new, recursive = TRUE, showWarnings = FALSE)

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

  # Additional steps to make vendoring work ----

  # 1. Check if `src/Makevars` exists
  makevars_exists <- file.exists("src/Makevars")

  # 2. If makevars exists, it should have a line that reads
  # `PKG_CPPFLAGS = -I../inst/include` or similar

  vendor_line <- paste0(" -I", new)

  if (isTRUE(makevars_exists)) {
    makevars <- readLines("src/Makevars")

    if (any(grepl("^PKG_CPPFLAGS", makevars))) {
      cat("There is a `PKG_CPPFLAGS` line in src/Makevars. It will be modified.\n")

      # which line contains `PKG_CPPFLAGS`?
      cppflags_line <- grep("^PKG_CPPFLAGS", makevars)

      # append the vendoring line
      if (!grepl(vendor_line, makevars[cppflags_line])) {
        makevars[cppflags_line] <- paste0(makevars[cppflags_line], vendor_line)
      }

      writeLines(makevars, "src/Makevars")
    } else {
      # add the line
      makevars <- c(makevars, paste0("PKG_CPPFLAGS = ", vendor_line))

      writeLines(makevars, "src/Makevars")
    }

    cat("The existing src/Makevars was modified. Please check it.\n")
  } else {
    # create the file
    writeLines(paste0("PKG_CPPFLAGS = ", vendor_line), "src/Makevars")

    # warn about the change
    cat("A new src/Makevars file was created.\n")
  }

  # 3. `DESCRIPTION` now should not have `LinkingTo: cpp11` or `LinkingTo: \n\tcpp11`
  description <- readLines("DESCRIPTION")

  cpp11_in_desc <- any(
    grepl("LinkingTo: cpp11", description),
    grepl("LinkingTo: ", description),
    grepl("    cpp11", description)
  )

  if (isTRUE(cpp11_in_desc)) {
    # remove the lines
    description <- description[!grepl("LinkingTo: cpp11", description)]
    description <- description[!grepl("LinkingTo: ", description)]
    description <- description[!grepl("    cpp11", description)]

    writeLines(description, "DESCRIPTION")

    # warn about the change
    cat("`LinkingTo: cpp11` was removed from DESCRIPTION.\n")
  }

  invisible(new)
}
