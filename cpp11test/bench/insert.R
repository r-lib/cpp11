pkgload::load_all("cpp11test")

bench::press(
  len = as.integer(10^(0:4)),
  {
    bench::mark(
      cpp11_insert_(len)
    )
  }
)
