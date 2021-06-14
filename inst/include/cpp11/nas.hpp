#pragma once

#include "cpp11/r_bool.hpp"
#include "cpp11/logicals.hpp"
#include "cpp11/r_string.hpp"


namespace cpp11 {

  template <typename T> struct na{};

  template <> struct na<double> { const static double value; };
  const double na<double>::value = NA_REAL;

  template <> struct na<int> { const static int value; };
  const int na<int>::value = NA_INTEGER;

  template <> struct na<r_bool> { const static r_bool value; };
  const r_bool na<r_bool>::value = NA_LOGICAL;

  template <> struct na<r_string> { const static r_string value; };
  const r_string na<r_string>::value = NA_STRING;

}

