#include "cpp11/doubles.hpp"

[[cpp11::register]] SEXP cpp11_push_and_truncate_(SEXP size_sexp) {
  R_xlen_t size = INTEGER(size_sexp)[0];

  cpp11::writable::doubles out(size);

  // Fill it
  for (R_xlen_t i = 0; i < size; ++i) {
    out.push_back(0);
  }

  // Push 1 more past the existing capacity,
  // doubling the capacity
  out.push_back(0);

  // Truncate back to `size + 1` size and return result.
  return SEXP(out);
}
