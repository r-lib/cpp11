pkgload::load_all("cpp11test")

bench::press(len = as.integer(10^(0:6)), {
  bench::mark(
    assign_cpp11_(n = len, 123L),
    assign_rcpp_(n = len, 123L),
    iterations = 20
  )
})[c("expression", "len", "min", "mem_alloc", "n_itr", "n_gc")]

# Longer benchmark, lots of gc
len <- as.integer(10^7)
bench::mark(
  cpp11 = cpp11_push_and_truncate_(len),
  rcpp = rcpp_push_and_truncate_(len),
  min_iterations = 200
)[c("expression", "min", "mem_alloc", "n_itr", "n_gc")]

bench::press(len = as.integer(10^(0:6)), {
  bench::mark(
    grow_strings_cpp11_(len, 123L),
    grow_strings_rcpp_(len, 123L),
    grow_strings_manual_(len, 123L),
    iterations = 20
  )
})[c("expression", "len", "min", "mem_alloc", "n_itr", "n_gc")]

# Longer benchmark, lots of gc
len <- as.integer(10^7)
bench::mark(
  cpp11 = cpp11_grow_strings_(len),
  rcpp = rcpp_grow_strings_(len),
  manual = manual_grow_strings_(len),
  min_iterations = 200
)[c("expression", "min", "mem_alloc", "n_itr", "n_gc")]
