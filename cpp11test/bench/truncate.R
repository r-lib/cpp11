pkgload::load_all("cpp11test")

bench::press(len = as.integer(10 ^ (0:6)),
  {
    bench::mark(
      cpp11_push_and_truncate_(len),
      min_iterations = 100
    )
  }
)

# Longer benchmark, lots of gc
len <- as.integer(10 ^ 7)
bench::mark(
  cpp11_push_and_truncate_(len),
  min_iterations = 200
)
