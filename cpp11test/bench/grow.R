pkgload::load_all("cpp11test")

bench::press(len = 10^(0:7), {
  bench::mark(
    .Call(cpp11_grow_, len)
  )
})
