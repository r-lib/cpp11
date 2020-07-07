#pragma once

#include <cmath>              // for modf
#include <initializer_list>   // for initializer_list
#include <string>             // for string, basic_string
#include <type_traits>        // for decay, enable_if, is_same, is_convertible
#include "cpp11/R.hpp"        // for SEXP, SEXPREC, Rf_xlength, R_xlen_t
#include "cpp11/protect.hpp"  // for stop, protect, safe, protect::function

namespace cpp11 {

template <typename T>
using is_constructible_from_sexp =
    typename std::enable_if<(std::is_class<typename std::decay<T>::type>::value ||
                             std::is_same<T, SEXP>::value) &&
                                std::is_constructible<T, SEXP>::value,
                            typename std::decay<T>::type>::type;

template <typename T>
is_constructible_from_sexp<T> as_cpp(SEXP from) {
  return from;
}

template <typename T>
using is_integral = typename std::enable_if<
    std::is_integral<T>::value &&
        !std::is_same<typename std::decay<T>::type, bool>::value &&
        !std::is_same<typename std::decay<T>::type, char>::value,
    typename std::decay<T>::type>::type;

template <typename T>
using is_integral_value = typename std::enable_if<
    std::is_integral<T>::value &&
        !std::is_same<typename std::decay<T>::type, bool>::value &&
        !std::is_same<typename std::decay<T>::type, char>::value,
    typename std::decay<T>::type>::value;

// https://stackoverflow.com/a/1521682/2055486
//
inline bool is_convertable_without_loss_to_integer(double value) {
  double int_part;
  return std::modf(value, &int_part) == 0.0;
}

template <typename T>
is_integral<T> as_cpp(SEXP from) {
  if (Rf_isInteger(from)) {
    if (Rf_xlength(from) == 1) {
      return INTEGER_ELT(from, 0);
    }
  } else if (Rf_isReal(from)) {
    if (Rf_xlength(from) == 1) {
      double value = REAL_ELT(from, 0);
      if (is_convertable_without_loss_to_integer(value)) {
        return value;
      }
    }
  }

  stop("Expected single integer value");

  return T();
}

template <typename T>
using is_logical =
    typename std::enable_if<std::is_same<typename std::decay<T>::type, bool>::value,
                            typename std::decay<T>::type>::type;
template <typename T>
is_logical<T> as_cpp(SEXP from) {
  if (Rf_isLogical(from)) {
    if (Rf_xlength(from) == 1) {
      return LOGICAL_ELT(from, 0) == 1;
    }
  }

  stop("Expected single logical value");

  return T();
}

template <typename T>
using is_floating_point_value =
    typename std::enable_if<std::is_floating_point<T>::value, T>::type;

template <typename T>
is_floating_point_value<T> as_cpp(SEXP from) {
  if (Rf_isReal(from)) {
    if (Rf_xlength(from) == 1) {
      return REAL_ELT(from, 0);
    }
  }
  // All integers can be coerced to doubles, so we just convert them.
  if (Rf_isInteger(from)) {
    if (Rf_xlength(from) == 1) {
      return INTEGER_ELT(from, 0);
    }
  }
  stop("Expected single double value");

  return T();
}

template <typename T>
using is_char =
    typename std::enable_if<std::is_same<typename std::decay<T>::type, char>::value,
                            typename std::decay<T>::type>::type;
template <typename T>
is_char<T> as_cpp(SEXP from) {
  if (Rf_isString(from)) {
    if (Rf_xlength(from) == 1) {
      const char* c_p = nullptr;
      unwind_protect([&] { c_p = Rf_translateCharUTF8(STRING_ELT(from, 0)); });
      return c_p[0];
    }
  }
  stop("Expected string vector of length 1");

  return T();
}

template <typename T>
using is_constructible_from_const_char = typename std::enable_if<
    std::is_constructible<typename std::decay<T>::type, const char*>::value &&
        !std::is_constructible<T, SEXP>::value,
    typename std::decay<T>::type>::type;

template <typename T>
is_constructible_from_const_char<T> as_cpp(SEXP from) {
  if (Rf_isString(from)) {
    if (Rf_xlength(from) == 1) {
      const char* c_p = nullptr;
      // TODO: use vmaxget / vmaxset here?
      unwind_protect([&] { c_p = Rf_translateCharUTF8(STRING_ELT(from, 0)); });
      return {c_p};
    }
  }
  stop("Expected string vector of length 1");

  return T(nullptr);
}

template <typename T, is_integral<T>* = nullptr>
inline SEXP as_sexp(T from) {
  return safe[Rf_ScalarInteger](from);
}

template <typename T, is_floating_point_value<T>* = nullptr>
inline SEXP as_sexp(T from) {
  return safe[Rf_ScalarReal](from);
}

inline SEXP as_sexp(const std::string& from) {
  SEXP res;
  unwind_protect([&] { res = Rf_ScalarString(Rf_mkCharCE(from.c_str(), CE_UTF8)); });
  return res;
}

template <typename T>
using is_bool =
    typename std::enable_if<std::is_same<typename std::decay<T>::type, bool>::value,
                            typename std::decay<T>::type>::type;

template <typename T, is_bool<T> = false>
inline SEXP as_sexp(T from) {
  return safe[Rf_ScalarLogical](from);
}

template <typename C, typename T = typename C::value_type,
          typename std::enable_if<!std::is_convertible<C, SEXP>::value,
                                  is_integral<T>>::type* = nullptr>
inline SEXP as_sexp(C from) {
  R_xlen_t size = from.size();
  SEXP data = safe[Rf_allocVector](INTSXP, size);

  auto it = from.begin();
  int* data_p = INTEGER(data);
  for (R_xlen_t i = 0; i < size; ++i, ++it) {
    data_p[i] = *it;
  }
  return data;
}

inline SEXP as_sexp(std::initializer_list<int> from) {
  return as_sexp<std::initializer_list<int>>(from);
}

template <typename C, typename T = typename C::value_type,
          is_floating_point_value<T>* = nullptr>
inline SEXP as_sexp(C from) {
  R_xlen_t size = from.size();
  SEXP data = safe[Rf_allocVector](REALSXP, size);

  auto it = from.begin();
  double* data_p = REAL(data);
  for (R_xlen_t i = 0; i < size; ++i, ++it) {
    data_p[i] = *it;
  }
  return data;
}

inline SEXP as_sexp(std::initializer_list<double> from) {
  return as_sexp<std::initializer_list<double>>(from);
}

template <typename C, typename T = typename C::value_type, is_bool<T>* = nullptr>
inline SEXP as_sexp(C from) {
  R_xlen_t size = from.size();
  SEXP data = safe[Rf_allocVector](LGLSXP, size);

  auto it = from.begin();
  int* data_p = LOGICAL(data);
  for (R_xlen_t i = 0; i < size; ++i, ++it) {
    data_p[i] = *it;
  }
  return data;
}

inline SEXP as_sexp(std::initializer_list<bool> from) {
  return as_sexp<std::initializer_list<bool>>(from);
}

template <typename T>
using is_convertible_to_std_string = typename std::enable_if<
    std::is_convertible<typename std::decay<T>::type, std::string>::value &&
        !std::is_convertible<typename std::decay<T>::type, const char*>::value,
    typename std::decay<T>::type>::type;

template <typename C, typename T = typename C::value_type,
          is_convertible_to_std_string<T>* = nullptr>
inline SEXP as_sexp(C from) {
  R_xlen_t size = from.size();

  SEXP data;
  try {
    data = PROTECT(safe[Rf_allocVector](STRSXP, size));

    auto it = from.begin();
    for (R_xlen_t i = 0; i < size; ++i, ++it) {
      SET_STRING_ELT(data, i,
                     safe[Rf_mkCharCE](static_cast<std::string>(*it).c_str(), CE_UTF8));
    }
  } catch (const unwind_exception& e) {
    UNPROTECT(1);
    throw e;
  }

  UNPROTECT(1);
  return data;
}
template <typename T>
using is_convertible_to_const_char = typename std::enable_if<
    std::is_convertible<typename std::decay<T>::type, const char*>::value &&
        !std::is_convertible<typename std::decay<T>::type, SEXP>::value,
    typename std::decay<T>::type>::type;

template <typename C, typename T = typename C::value_type,
          is_convertible_to_const_char<T>* = nullptr>
inline SEXP as_sexp(C from) {
  R_xlen_t size = from.size();

  SEXP data;
  try {
    data = PROTECT(safe[Rf_allocVector](STRSXP, size));

    auto it = from.begin();
    for (R_xlen_t i = 0; i < size; ++i, ++it) {
      SET_STRING_ELT(data, i, safe[Rf_mkCharCE](static_cast<const char*>(*it), CE_UTF8));
    }
  } catch (const unwind_exception& e) {
    UNPROTECT(1);
    throw e;
  }

  UNPROTECT(1);
  return data;
}

inline SEXP as_sexp(std::initializer_list<const char*> from) {
  return as_sexp<std::initializer_list<const char*>>(from);
}

inline SEXP as_sexp(SEXP from) { return from; }

}  // namespace cpp11
