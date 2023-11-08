#include <numeric>
#include "headers/integers.hpp"

[[cpp11::register]] double sum_int_for_(cpp11::integers x) {
  double sum = 0.;
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum += x[i];
  }

  return sum;
}

[[cpp11::register]] double sum_int_for2_(SEXP x_) {
  cpp11::integers x(x_, false);

  double sum = 0.;
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum += x[i];
  }
  return sum;
}

[[cpp11::register]] double sum_int_foreach_(cpp11::integers x) {
  double sum = 0.;
  for (auto v : x) {
    sum += v;
  }

  return sum;
}

[[cpp11::register]] double sum_int_accumulate_(cpp11::integers x) {
  return std::accumulate(x.cbegin(), x.cend(), 0.);
}
