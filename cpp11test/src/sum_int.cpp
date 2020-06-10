#include "cpp11/integers.hpp"

[[cpp11::export]] int sum_int_for_(cpp11::integers x) {
  int sum = 0;
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum += x[i];
  }

  return sum;
}
