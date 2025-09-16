#include "cpp11/doubles.hpp"
using namespace cpp11;

// Test: documented + documented

/* roxygen start
@title Roxygenise C++ function III
@param x numeric value
@description Dummy function to test roxygen2. It adds 3.0 to a double.
@export
@examples roxcpp3_(1.0)
roxygen end */
[[cpp11::register]] double roxcpp3_(double x) {
  double y = x + 3.0;
  return y;
}

/* roxygen start
@title Roxygenise C++ function IV
@param x numeric value
@description Dummy function to test roxygen2. It adds 4.0 to a double.
@export
@examples roxcpp4_(1.0)
roxygen end */
[[cpp11::register]] double roxcpp4_(double x) {
  double y = x + 4.0;
  return y;
}
