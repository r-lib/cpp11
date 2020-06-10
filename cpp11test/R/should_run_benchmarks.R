should_run_benchmarks <- function() {
  isTRUE(as.logical(Sys.getenv("CPP11TEST_SHOULD_RUN_BENCHMARKS", "false")))
}
