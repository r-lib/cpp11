#include "cpp11/doubles.hpp"

[[cpp11::register]] SEXP cpp11_push_and_truncate_(SEXP size_sexp) {
  R_xlen_t size = INTEGER(size_sexp)[0];

  // Allocate `size` worth of doubles (filled with garbage data)
  cpp11::writable::doubles out(size);

  // Push 1 more past the existing length/capacity,
  // doubling the capacity for cpp11 vectors
  out.push_back(0);

  // Truncate back to `size + 1` size and return result.
  return SEXP(out);
}
