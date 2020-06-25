#include "cpp11/doubles.hpp"

[[cpp11::register]] SEXP cpp11_add_vec_for_(cpp11::writable::doubles x, double num) {
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    double cur = x[i];
    x[i] = cur + num;
  }

  return x;
}
