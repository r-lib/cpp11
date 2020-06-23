local_package <- function() {
  dir <- tempfile()
  dir.create(dir)

  writeLines("Package: testPkg", file.path(dir, "DESCRIPTION"))
  desc::desc(dir)
}

pkg_path <- function(pkg) {
  dirname(pkg$.__enclos_env__$private$path)
}

glue_str <- function(...) {
  glue::as_glue(unlist(list(...)))
}
