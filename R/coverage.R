cpp11_coverage <- function(...) {
  old <- options(covr.filter_non_package = FALSE, covr.gcov_additional_paths = ".*/cpp11/")
  on.exit(options(old))

  cpp11_coverage <- covr::package_coverage(".", ...)

  cpp11test_coverage <- covr::package_coverage("cpp11test", ...)

  cpp11test_coverage <- cpp11test_coverage[grepl("include/cpp11", covr::display_name(cpp11test_coverage))]
  attr(cpp11test_coverage, "package")$path <- sub("cpp11/include.*", "cpp11", covr::display_name(cpp11test_coverage)[[1]])

  cov <- c(cpp11_coverage, cpp11test_coverage)
  attributes(cov) <- attributes(cpp11_coverage)

  cov
}
