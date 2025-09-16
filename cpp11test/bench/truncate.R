pkgload::load_all("cpp11test")

bench::press(len = as.integer(10 ^ (0:6)),
  {
    bench::mark(
      cpp11 = cpp11_push_and_truncate_(len),
      rcpp = rcpp_push_and_truncate_(len),
      check = FALSE,
      min_iterations = 1000
    )
  }
)[c("expression", "len", "min", "mem_alloc", "n_itr", "n_gc")]

# Longer benchmark, lots of gc
len <- as.integer(10 ^ 7)
bench::mark(
  cpp11 = cpp11_push_and_truncate_(len),
  rcpp = rcpp_push_and_truncate_(len),
  min_iterations = 200
)[c("expression", "min", "mem_alloc", "n_itr", "n_gc")]
