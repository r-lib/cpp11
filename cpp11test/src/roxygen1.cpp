#include "cpp11/doubles.hpp"
using namespace cpp11;

// Test: not documented + documented

// Not Roxygenised C++ function I
[[cpp11::register]] double notroxcpp1_(double x) {
  double y = x + 1.0;
  return y;
}

/* roxygen start
@title Roxygenise C++ function II
@param x numeric value
@description Dummy function to test roxygen2. It adds 2.0 to a double.
@export
@examples roxcpp2_(1.0)
roxygen end */
[[cpp11::register]] double roxcpp2_(double x) {
  double y = x + 2.0;
  return y;
}
