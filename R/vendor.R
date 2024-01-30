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
#' @param path The path to vendor the code into. The default is `src/vendor/`.
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
  if (dir.exists(path)) {
    cat(
      sprintf(
        "The directory '%s' already exists. Do you want to overwrite it?\n",
        path
      )
    )
    if (interactive()) {
      if (utils::menu(c("Yes", "No"), graphics = FALSE) == 1L) {
        unlink(path, recursive = TRUE)
      } else {
        return(FALSE)
      }
    } else {
      message("Running in non-interactive mode. Exiting.")
      return(FALSE)
    }
  }

  dir.create(path, recursive = TRUE, showWarnings = FALSE)

  # Vendor cpp11 ----

  dir.create(
    file.path(path, "cpp11"),
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

  # 1. Check if `src/Makevars` exists
  makevars_exists <- file.exists("src/Makevars")
  makevars.win_exists <- file.exists("src/Makevars.win")

  # 2. If makevars exists, it should have a line that reads
  # `PKG_CPPFLAGS = -I../inst/include` or similar

  vendor_line <- " -I vendor/"

  makevars_file <- "src/Makevars"
  if (isTRUE(makevars_exists)) {
    makevars <- readLines(makevars_file)
    alter_makevars(makevars, makevars_file, vendor_line)
  } else {
    create_makevars(makevars_file)
  }

  makevars.win_file <- "src/Makevars.win"
  if (isTRUE(makevars.win_exists)) {
    makevars.win <- readLines(makevars.win_file)
    alter_makevars(makevars.win, makevars.win_file, vendor_line)
  } else {
    create_makevars(makevars.win_file)
  }

  # 3. `DESCRIPTION` now should not have `LinkingTo: cpp11armadillo` or
  #    `LinkingTo: \n\tcpp11armadillo`
  description_file <- "DESCRIPTION"
  description <- readLines(description_file)

  cpp11armadillo_in_desc <- any(
    grepl("LinkingTo: cpp11, cpp11armadillo", description),
    grepl("LinkingTo: ", description),
    grepl("    cpp11,", description),
    grepl("    cpp11armadillo", description)
  )

  if (isTRUE(cpp11armadillo_in_desc)) {
    # remove the lines
    description <- description[!grepl(
      "LinkingTo: cpp11, cpp11armadillo",
      description
    )]
    description <- description[!grepl("LinkingTo: ", description)]
    description <- description[!grepl("    cpp11,", description)]
    description <- description[!grepl("    cpp11armadillo", description)]

    writeLines(description, description_file)

    # warn about the change
    cat("`LinkingTo: cpp11, cpp11armadillo` was removed from DESCRIPTION.\n")
  }

  invisible(path)
}

alter_makevars <- function(makevars, makevars_file, vendor_line) {
  if (any(grepl("^PKG_CPPFLAGS", makevars))) {
    cat(
      "There is a `PKG_CPPFLAGS` line in src/Makevars. It will be modified.\n"
    )

    # which line contains `PKG_CPPFLAGS`?
    cppflags_line <- grep("^PKG_CPPFLAGS", makevars)

    # append the vendoring line
    if (!grepl(vendor_line, makevars[cppflags_line])) {
      makevars[cppflags_line] <- paste0(makevars[cppflags_line], vendor_line)
    }

    writeLines(makevars, makevars_file)
  } else {
    # add the line
    makevars <- c(makevars, paste0("PKG_CPPFLAGS = ", vendor_line))

    writeLines(makevars, makevars_file)
  }
}

create_makevars <- function(filename, vendor_line) {
  # create the file
  writeLines(paste0("PKG_CPPFLAGS = ", vendor_line), filename)

  # warn about the change
  cat("A new src/Makevars file was created.\n")
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
