#pragma once

#include <algorithm>         // for min
#include <array>             // for array
#include <initializer_list>  // for initializer_list

#include "cpp11/R.hpp"                // for SEXP, SEXPREC, Rf_all...
#include "cpp11/attribute_proxy.hpp"  // for attribute_proxy
#include "cpp11/named_arg.hpp"        // for named_arg
#include "cpp11/protect.hpp"          // for safe
#include "cpp11/r_bool.hpp"           // for r_bool
#include "cpp11/r_vector.hpp"         // for r_vector, r_vector<>::proxy
#include "cpp11/sexp.hpp"             // for sexp

// Specializations for logicals

namespace cpp11 {

template <>
inline SEXPTYPE r_vector<r_bool>::get_sexptype() {
  return LGLSXP;
}

template <>
inline typename r_vector<r_bool>::underlying_type r_vector<r_bool>::get_elt(SEXP x,
                                                                            R_xlen_t i) {
  // NOPROTECT: likely too costly to unwind protect every elt
  return LOGICAL_ELT(x, i);
}

template <>
inline typename r_vector<r_bool>::underlying_type* r_vector<r_bool>::get_p(bool is_altrep,
                                                                           SEXP data) {
  if (is_altrep) {
    return nullptr;
  } else {
    return LOGICAL(data);
  }
}

template <>
inline void r_vector<r_bool>::get_region(SEXP x, R_xlen_t i, R_xlen_t n,
                                         typename r_vector::underlying_type* buf) {
  // NOPROTECT: likely too costly to unwind protect here
  LOGICAL_GET_REGION(x, i, n, buf);
};

template <>
inline bool r_vector<r_bool>::const_iterator::use_buf(bool is_altrep) {
  return is_altrep;
}

typedef r_vector<r_bool> logicals;

namespace writable {

template <>
inline void r_vector<r_bool>::set_elt(SEXP x, R_xlen_t i,
                                      typename r_vector::underlying_type value) {
  // NOPROTECT: Likely too costly to unwind protect every set elt
  SET_LOGICAL_ELT(x, i, value);
}

template <>
inline typename r_vector<r_bool>::proxy& r_vector<r_bool>::proxy::operator=(
    const r_bool& rhs) {
  if (is_altrep_) {
    SET_LOGICAL_ELT(data_, index_, rhs);
  } else {
    *p_ = rhs;
  }
  return *this;
}

inline bool operator==(const r_vector<r_bool>::proxy& lhs, r_bool rhs) {
  return static_cast<r_bool>(lhs).operator==(rhs);
}

template <>
inline r_vector<r_bool>::r_vector(std::initializer_list<named_arg> il)
    : cpp11::r_vector<r_bool>(safe[Rf_allocVector](LGLSXP, il.size())),
      capacity_(il.size()) {
  int n_protected = 0;

  try {
    unwind_protect([&] {
      Rf_setAttrib(data_, R_NamesSymbol, Rf_allocVector(STRSXP, capacity_));
      SEXP names = PROTECT(Rf_getAttrib(data_, R_NamesSymbol));
      ++n_protected;
      auto it = il.begin();
      for (R_xlen_t i = 0; i < capacity_; ++i, ++it) {
        data_p_[i] = LOGICAL_ELT(it->value(), 0);
        SET_STRING_ELT(names, i, Rf_mkCharCE(it->name(), CE_UTF8));
      }
      UNPROTECT(n_protected);
    });
  } catch (const unwind_exception& e) {
    UNPROTECT(n_protected);
    throw e;
  }
}

typedef r_vector<r_bool> logicals;

}  // namespace writable

}  // namespace cpp11
