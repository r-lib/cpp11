#include "headers/doubles.hpp"

[[cpp11::register]] SEXP cpp11_insert_(SEXP num_sxp) {
  R_xlen_t num = INTEGER(num_sxp)[0];

  R_xlen_t i = 0;
  cpp11::writable::doubles out;
  while (i < num) {
    out.insert(0, i++);
  }
  return SEXP(out);
}
