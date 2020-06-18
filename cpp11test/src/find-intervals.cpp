#include <algorithm>
#include "cpp11.hpp"
using namespace cpp11;

#include <Rcpp.h>
#include <algorithm>
using namespace Rcpp;

[[cpp11::export]] SEXP remove_altrep(SEXP x) {
  SEXP out = PROTECT(Rf_allocVector(REALSXP, Rf_xlength(x)));
  memcpy(REAL(out), REAL(x), Rf_xlength(x));

  UNPROTECT(1);
  return out;
}

[[cpp11::export]] double upper_bound(doubles x, doubles breaks) {
  auto pos = std::upper_bound(breaks.begin(), breaks.end(), x[0]);
  return std::distance(breaks.begin(), pos);
}

[[cpp11::export]] integers findInterval2(doubles x, doubles breaks) {
  writable::integers out(x.size());
  auto out_it = out.begin();

  for (auto&& val : x) {
    auto pos = std::upper_bound(breaks.begin(), breaks.end(), val);
    *out_it = std::distance(breaks.begin(), pos);
    ++out_it;
  }
  return out;
}
[[cpp11::export]] integers findInterval2_5(doubles x, doubles breaks) {
  writable::integers out(x.size());
  auto out_it = out.begin();
  auto bb = breaks.begin();
  auto be = breaks.end();

  for (auto&& val : x) {
    auto pos = std::upper_bound(bb, be, val);
    *out_it = std::distance(bb, pos);
    ++out_it;
  }
  return out;
}

// This version avoids the overhead of the cpp11 iterator types
[[cpp11::export]] integers findInterval3(doubles x, doubles breaks) {
  writable::integers out(x.size());
  auto out_it = out.begin();
  auto b = REAL(breaks);
  auto e = REAL(breaks) + Rf_xlength(breaks);
  double* pos;

  for (auto&& val : x) {
    pos = std::upper_bound(b, e, val);
    *out_it = std::distance(b, pos);
    ++out_it;
  }
  return out;
}

[[cpp11::export]] IntegerVector findInterval4(NumericVector x, NumericVector breaks) {
  IntegerVector out(x.size());

  NumericVector::iterator it, it_end, pos, b, e;
  IntegerVector::iterator out_it;
  it_end = x.end();
  b = breaks.begin();
  e = breaks.end();

  for (it = x.begin(), out_it = out.begin(); it != it_end; ++it, ++out_it) {
    pos = std::upper_bound(b, e, *it);
    *out_it = std::distance(b, pos);
  }

  return out;
}

/* R code to benchmark these implementations
res <- bench::press(
  n1 = 10^seq(1, 3),
  n2 = 10^seq(1, 5),
  {
    x <- c(-n1, seq(-2, 2, length = n1 + 1), n1)
    y <- sort(round(stats::rt(n2, df = 2), 2))
    bench::mark(
      findInterval(x, y),
      findInterval2(x, y),
      findInterval2_5(x, y),
      findInterval3(x, y),
      findInterval4(x, y)
    )
  }
)
*/
