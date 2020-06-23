pkgload::load_all("cpp11test")

bench::press(n = 10000,
  bench::mark(
    protect_many_(n),
    protect_many_cpp11_(n),
    protect_many_sexp_(n),
    protect_many_preserve_(n),
    protect_many_rcpp_(n)
  )
)
