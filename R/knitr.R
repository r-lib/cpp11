eng_cpp11 = function(options) {
  if (options$eval) {
    source_cpp(code = options$code, env = knitr::knit_global(), clean = TRUE, quiet = FALSE)
  }
  options$engine <- "cpp"
  knitr::engine_output(options, options$code, '')
}

.onLoad <- function(libname, pkgname) {
  if (requireNamespace("knitr", quietly = TRUE)) {
    knitr::knit_engines$set(cpp11 = eng_cpp11)
  }
}
