cpp11_coverage <- function(...) {
  old <- options(covr.filter_non_package = FALSE, covr.gcov_additional_paths = ".*/cpp11/")
  on.exit(options(old))

  cov <- covr::package_coverage("cpp11test", ...)

  cov <- cov[grepl("include/cpp11", covr::display_name(cov))]
  attr(cov, "package")$path <- sub("cpp11/include.*", "cpp11", covr::display_name(cov)[[1]])

  cov
}
