#pragma once

#include <cstring>
#include <string>
#include <vector>

#ifndef CPP11_PARTIAL
#include "cpp11.hpp"
using namespace cpp11;
namespace writable = cpp11::writable;
#endif

#include <R_ext/Rdynload.h>

namespace cpp11 {
template <class T>
T& unmove(T&& t) {
  return t;
}
}  // namespace cpp11

#ifdef HAS_UNWIND_PROTECT
#define CPP11_UNWIND R_ContinueUnwind(err);
#else
#define CPP11_UNWIND \
  do {               \
  } while (false);
#endif

#define BEGIN_CPP11 \
  SEXP err;         \
  char buf[8192];   \
  buf[0] = '\0';    \
  try {
#define END_CPP11                                        \
  }                                                      \
  catch (cpp11::unwind_exception & e) {                  \
    err = e.token;                                       \
  }                                                      \
  catch (std::exception & e) {                           \
    strncpy(buf, e.what(), 8192 - 1);                    \
  }                                                      \
  catch (...) {                                          \
    strncpy(buf, "C++ error (unknown cause)", 8192 - 1); \
  }                                                      \
  if (buf[0] != '\0') {                                  \
    Rf_errorcall(R_NilValue, "%s", buf);                 \
  } else if (err != R_NilValue) {                        \
    CPP11_UNWIND                                         \
  }                                                      \
  return R_NilValue;
