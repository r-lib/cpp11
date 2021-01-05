#include <Rcpp.h>

// clang-format off
#ifdef __clang__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wattributes"
#endif

#ifdef __GNUC__
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wattributes"
#endif
// clang-format on

[[cpp11::register]] SEXP rcpp_sum_dbl_for_(SEXP x_sxp) {
  Rcpp::NumericVector x(x_sxp);
  R_xlen_t n = x.size();
  double sum = 0.;
  for (R_xlen_t i = 0; i < n; ++i) {
    sum += x[i];
  }
  return Rf_ScalarReal(sum);
}

[[cpp11::register]] SEXP rcpp_sum_int_for_(SEXP x_sxp) {
  Rcpp::IntegerVector x(x_sxp);
  R_xlen_t n = x.size();
  double sum = 0.;
  for (R_xlen_t i = 0; i < n; ++i) {
    sum += x[i];
  }
  return Rf_ScalarReal(sum);
}

[[cpp11::register]] SEXP rcpp_sum_dbl_foreach_(SEXP x_sxp) {
  Rcpp::NumericVector x(x_sxp);
  double sum = 0.;
  for (const auto& val : x) {
    sum += val;
  }
  return Rf_ScalarReal(sum);
}

[[cpp11::register]] SEXP rcpp_sum_dbl_accumulate_(SEXP x_sxp) {
  Rcpp::NumericVector x(x_sxp);
  return Rf_ScalarReal(std::accumulate(x.cbegin(), x.cend(), 0.));
}

[[cpp11::register]] SEXP rcpp_grow_(SEXP n_sxp) {
  R_xlen_t n = REAL(n_sxp)[0];
  Rcpp::NumericVector x;
  R_xlen_t i = 0;
  while (i < n) {
    x.push_back(i++);
  }

  return x;
}
