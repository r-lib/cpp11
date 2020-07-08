if (!covr::in_covr() && get("requireNamespace")("cpp11test", quietly = TRUE) && nzchar(system.file("tests", package = "cpp11test"))) {
  cpp11test::run_tests(reporter = testthat::default_reporter())
}
