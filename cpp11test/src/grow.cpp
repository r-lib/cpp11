#include "cpp11/doubles.hpp"

[[cpp11::export]] cpp11::writable::doubles grow_(R_xlen_t n) {
  cpp11::writable::doubles x;
  R_xlen_t i = 0;
  while (i < n) {
    x.push_back(i++);
  }

  return x;
}
