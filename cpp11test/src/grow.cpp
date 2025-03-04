#include "cpp11/complexes.hpp"
#include "cpp11/doubles.hpp"

[[cpp11::register]] cpp11::writable::doubles grow_(R_xlen_t n) {
  cpp11::writable::doubles x;
  R_xlen_t i = 0;
  while (i < n) {
    x.push_back(i++);
  }

  return x;
}

[[cpp11::register]] cpp11::writable::complexes grow_cplx_(R_xlen_t n) {
  cpp11::writable::complexes x;
  R_xlen_t i = 0;
  while (i < n) {
    x.push_back(std::complex<double>(i, i));
    i++;
  }

  return x;
}
