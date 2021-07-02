local_package <- function() {
  dir <- tempfile()
  dir.create(dir)
  withr::defer(unlink(dir, recursive = TRUE), parent.frame())

  writeLines("Package: testPkg", file.path(dir, "DESCRIPTION"))
  writeLines("useDynLib(testPkg, .registration = TRUE)", file.path(dir, "NAMESPACE"))
  desc::desc(dir)
}

pkg_path <- function(pkg) {
  dirname(pkg$.__enclos_env__$private$path)
}

get_funs <- function(path) {
  all_decorations <- decor::cpp_decorations(path, is_attribute = TRUE)
  get_registered_functions(all_decorations, "cpp11::register", quiet = FALSE)
}

get_package_name <- function(path) {
  desc::desc_get("Package", file = file.path(path, "DESCRIPTION"))
}

glue_str <- function(...) {
  glue::as_glue(unlist(list(...)))
}

read_file <- function(x) {
  readChar(x, file.size(x))
}

expect_error_free <- function(..., regexp = NA) {
  expect_error(..., regexp = regexp)
}
