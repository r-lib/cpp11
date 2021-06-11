#pragma once

#include "cpp11/r_bool.hpp"
#include "cpp11/r_string.hpp"


namespace cpp11 {

  template <typename T> struct na{};

  template <> struct na<double> { const static double value; };

  template <> struct na<int> { const static int value; };

  template <> struct na<r_bool> { const static r_bool value; };

  template <> struct na<r_string> { const static  r_string value; };
}

