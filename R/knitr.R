eng_cpp11 <- function(options) {
  if (options$eval) {
    cpp_source(
      code = options$code,
      env = knitr::knit_global(),
      clean = options$clean %||% TRUE,
      quiet = options$quiet %||% FALSE,
      cxx_std = options$cxx_std %||% Sys.getenv("CXX_STD", "CXX11")
    )
  }

  # Change the engine to cpp so that code formatting works
  options$engine <- "cpp"
  knitr::engine_output(options, options$code, "")
}
