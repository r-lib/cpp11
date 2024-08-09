#pragma once

#include <algorithm>         // for min
#include <array>             // for array
#include <initializer_list>  // for initializer_list

#include "R_ext/Arith.h"              // for NA_INTEGER
#include "cpp11/R.hpp"                // for SEXP, SEXPREC, Rf_allocVector
#include "cpp11/as.hpp"               // for as_sexp
#include "cpp11/attribute_proxy.hpp"  // for attribute_proxy
#include "cpp11/named_arg.hpp"        // for named_arg
#include "cpp11/protect.hpp"          // for safe
#include "cpp11/r_vector.hpp"         // for r_vector, r_vector<>::proxy
#include "cpp11/sexp.hpp"             // for sexp

// Specializations for integers

namespace cpp11 {

template <>
inline typename r_vector<int>::underlying_type r_vector<int>::get_elt(SEXP x,
                                                                      R_xlen_t i) {
  // NOPROTECT: likely too costly to unwind protect every elt
  return INTEGER_ELT(x, i);
}

template <>
inline SEXP r_vector<int>::valid_type(SEXP data) {
  if (data == nullptr) {
    throw type_error(INTSXP, NILSXP);
  }
  if (TYPEOF(data) != INTSXP) {
    throw type_error(INTSXP, TYPEOF(data));
  }
  return data;
}

template <>
inline typename r_vector<int>::underlying_type* r_vector<int>::get_p(bool is_altrep,
                                                                     SEXP data) {
  if (is_altrep) {
    return nullptr;
  } else {
    return INTEGER(data);
  }
}

template <>
inline void r_vector<int>::get_region(SEXP x, R_xlen_t i, R_xlen_t n,
                                      typename r_vector::underlying_type* buf) {
  // NOPROTECT: likely too costly to unwind protect here
  INTEGER_GET_REGION(x, i, n, buf);
};

template <>
inline bool r_vector<int>::const_iterator::use_buf(bool is_altrep) {
  return is_altrep;
}

typedef r_vector<int> integers;

namespace writable {

template <>
inline SEXPTYPE r_vector<int>::get_sexptype() {
  return INTSXP;
}

template <>
inline void r_vector<int>::set_elt(SEXP x, R_xlen_t i,
                                   typename r_vector::underlying_type value) {
  SET_INTEGER_ELT(x, i, value);
}

template <>
inline r_vector<int>::proxy::operator int() const {
  if (p_ == nullptr) {
    // NOPROTECT: likely too costly to unwind protect every elt
    return INTEGER_ELT(data_, index_);
  } else {
    return *p_;
  }
}

template <>
inline r_vector<int>::r_vector(std::initializer_list<named_arg> il)
    : cpp11::r_vector<int>(safe[Rf_allocVector](INTSXP, il.size())),
      capacity_(il.size()) {
  int n_protected = 0;

  try {
    unwind_protect([&] {
      Rf_setAttrib(data_, R_NamesSymbol, Rf_allocVector(STRSXP, capacity_));
      SEXP names = PROTECT(Rf_getAttrib(data_, R_NamesSymbol));
      ++n_protected;
      auto it = il.begin();
      for (R_xlen_t i = 0; i < capacity_; ++i, ++it) {
        data_p_[i] = INTEGER_ELT(it->value(), 0);
        SET_STRING_ELT(names, i, Rf_mkCharCE(it->name(), CE_UTF8));
      }
      UNPROTECT(n_protected);
    });
  } catch (const unwind_exception& e) {
    UNPROTECT(n_protected);
    throw e;
  }
}

template <>
inline void r_vector<int>::push_back(int value) {
  while (length_ >= capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ *= 2);
  }
  if (is_altrep_) {
    // NOPROTECT: likely too costly to unwind protect every elt
    SET_INTEGER_ELT(data_, length_, value);
  } else {
    data_p_[length_] = value;
  }
  ++length_;
}

typedef r_vector<int> integers;

}  // namespace writable

template <>
inline int na() {
  return NA_INTEGER;
}

// forward declaration

typedef r_vector<double> doubles;

inline integers as_integers(SEXP x) {
  if (TYPEOF(x) == INTSXP) {
    return integers(x);
  } else if (TYPEOF(x) == REALSXP) {
    doubles xn(x);
    writable::integers ret(xn.size());
    std::transform(xn.begin(), xn.end(), ret.begin(), [](double value) {
      if (ISNA(value)) {
        return NA_INTEGER;
      }
      if (!is_convertible_without_loss_to_integer(value)) {
        throw std::runtime_error("All elements must be integer-like");
      }
      return static_cast<int>(value);
    });
    return ret;
  }

  throw type_error(INTSXP, TYPEOF(x));
}

}  // namespace cpp11
