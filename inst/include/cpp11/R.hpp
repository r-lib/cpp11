#pragma once

#define R_NO_REMAP
#define STRICT_R_HEADERS
#include "Rinternals.h"
#undef STRICT_R_HEADERS
#undef R_NO_REMAP

// clang-format off
#ifdef __clang__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wattributes"
#endif

#ifdef __GNUC__
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wattributes"
#endif
// clang-format on

#include "cpp11/altrep.hpp"
