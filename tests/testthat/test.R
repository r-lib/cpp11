if (!covr::in_covr() && requireNamespace("cpp11test") && nzchar(system.file("tests", package = "cpp11test"))) {
  cpp11test::run_tests(reporter = testthat::default_reporter())
}
