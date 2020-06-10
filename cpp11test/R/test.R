#' Run the cpp11 tests
#' @inheritParams testthat::test_check
#' @export
run_tests <- function(reporter = testthat::default_reporter()) {
  if (interactive()) {
    if (pkgload::is_dev_package("cpp11")) {
      # load cpp11
      pkgload::load_all(system.file(".", package = "cpp11"))

      # load cpp11test
      pkgload::load_all(system.file("cpp11test", package = "cpp11"))
    } else {
      # load cpp11
      pkgload::load_all("..")

      # load cpp11test
      pkgload::load_all()
    }
  }

  old <- getwd()
  on.exit(setwd(old))
  setwd(system.file("tests", package = "cpp11test"))

  library(testthat)
  test_check("cpp11test", reporter = reporter)
}
