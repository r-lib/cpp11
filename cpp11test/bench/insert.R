pkgload::load_all()

bench::press(
  len = as.integer(10^(0:4)),
  {
    bench::mark(
      .Call(cpp11_insert_, len)
    )
  }
)
