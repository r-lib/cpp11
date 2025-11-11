#include "cpp11/doubles.hpp"
using namespace cpp11;

// Test: documented + not documented + documented

/* roxygen start
@title Roxygenise C++ function V
@param x numeric value
@description Dummy function to test roxygen2. It adds 5.0 to a double.
@export
@examples roxcpp5_(1.0)
roxygen end */
[[cpp11::register]] double roxcpp5_(double x) {
  double y = x + 5.0;
  return y;
}

// Not Roxygenised C++ function VI
[[cpp11::register]] double notroxcpp6_(double x) {
  double y = x + 6.0;
  return y;
}

/* roxygen start
@title Roxygenise C++ function VII
@param x numeric value
@description Dummy function to test roxygen2. It adds 7.0 to a double.
@export
@examples
my_fun <- function(x) {
  roxcpp7_(x)
}
@seealso \code{\link{roxcpp1_}}
roxygen end */
[[cpp11::register]] double roxcpp7_(double x) {
  double y = x + 7.0;
  return y;
}
