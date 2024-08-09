#include "cpp11/strings.hpp"

// Test benchmark for string proxy assignment performance.
// We don't unwind_protect() before each `SET_STRING_ELT()` call,
// as that kills performance.
[[cpp11::register]] cpp11::writable::strings string_proxy_assignment_() {
  R_xlen_t size = 100000;

  cpp11::writable::strings x(size);

  cpp11::r_string elt(NA_STRING);

  for (R_xlen_t i = 0; i < size; ++i) {
    x[i] = elt;
  }

  return x;
}

// Test benchmark for string push back performance.
// We don't unwind_protect() before each `SET_STRING_ELT()` call,
// as that kills performance.
[[cpp11::register]] cpp11::writable::strings string_push_back_() {
  R_xlen_t size = 100000;

  cpp11::writable::strings x;

  cpp11::r_string elt(NA_STRING);

  for (R_xlen_t i = 0; i < size; ++i) {
    x.push_back(elt);
  }

  return x;
}
