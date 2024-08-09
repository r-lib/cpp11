#pragma once

#include <algorithm>         // for min
#include <array>             // for array
#include <cstdint>           // for uint8_t
#include <initializer_list>  // for initializer_list

#include "Rversion.h"
#include "cpp11/R.hpp"                // for RAW, SEXP, SEXPREC, Rf_allocVector
#include "cpp11/attribute_proxy.hpp"  // for attribute_proxy
#include "cpp11/named_arg.hpp"        // for named_arg
#include "cpp11/protect.hpp"          // for safe
#include "cpp11/r_vector.hpp"         // for r_vector, r_vector<>::proxy
#include "cpp11/sexp.hpp"             // for sexp

// Specializations for raws

namespace cpp11 {

namespace traits {
template <>
struct get_underlying_type<uint8_t> {
  using type = Rbyte;
};
}  // namespace traits

template <>
inline SEXP r_vector<uint8_t>::valid_type(SEXP data) {
  if (data == nullptr) {
    throw type_error(RAWSXP, NILSXP);
  }
  if (TYPEOF(data) != RAWSXP) {
    throw type_error(RAWSXP, TYPEOF(data));
  }
  return data;
}

template <>
inline uint8_t r_vector<uint8_t>::operator[](const R_xlen_t pos) const {
  // NOPROTECT: likely too costly to unwind protect every elt
  return is_altrep_ ? RAW_ELT(data_, pos) : data_p_[pos];
}

template <>
inline typename r_vector<uint8_t>::underlying_type* r_vector<uint8_t>::get_p(
    bool is_altrep, SEXP data) {
  if (is_altrep) {
    return nullptr;
  } else {
    return RAW(data);
  }
}

template <>
inline void r_vector<uint8_t>::get_region(
    SEXP x, R_xlen_t i, R_xlen_t n,
    typename traits::get_underlying_type<uint8_t>::type* buf) {
  // NOPROTECT: likely too costly to unwind protect here
  RAW_GET_REGION(x, i, n, buf);
};

template <>
inline bool r_vector<uint8_t>::const_iterator::use_buf(bool is_altrep) {
  return is_altrep;
}

typedef r_vector<uint8_t> raws;

namespace writable {

template <>
inline SEXPTYPE r_vector<uint8_t>::get_sexptype() {
  return RAWSXP;
}

template <>
inline void r_vector<uint8_t>::set_elt(
    SEXP x, R_xlen_t i, typename traits::get_underlying_type<uint8_t>::type value) {
#if R_VERSION >= R_Version(4, 2, 0)
  SET_RAW_ELT(x, i, value);
#else
  RAW(x)[i] = value;
#endif
}

template <>
inline typename r_vector<uint8_t>::proxy& r_vector<uint8_t>::proxy::operator=(
    const uint8_t& rhs) {
  if (is_altrep_) {
    // NOPROTECT: likely too costly to unwind protect every set elt
    RAW(data_)[index_] = rhs;
  } else {
    *p_ = rhs;
  }
  return *this;
}

template <>
inline r_vector<uint8_t>::proxy::operator uint8_t() const {
  if (p_ == nullptr) {
    // NOPROTECT: likely too costly to unwind protect every elt
    return RAW(data_)[index_];
  } else {
    return *p_;
  }
}

template <>
inline r_vector<uint8_t>::r_vector(std::initializer_list<named_arg> il)
    : cpp11::r_vector<uint8_t>(safe[Rf_allocVector](RAWSXP, il.size())),
      capacity_(il.size()) {
  int n_protected = 0;

  try {
    unwind_protect([&] {
      Rf_setAttrib(data_, R_NamesSymbol, Rf_allocVector(STRSXP, capacity_));
      SEXP names = PROTECT(Rf_getAttrib(data_, R_NamesSymbol));
      ++n_protected;

      auto it = il.begin();
      for (R_xlen_t i = 0; i < capacity_; ++i, ++it) {
        data_p_[i] = RAW_ELT(it->value(), 0);
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
inline void r_vector<uint8_t>::push_back(uint8_t value) {
  while (length_ >= capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ *= 2);
  }
  if (is_altrep_) {
    // NOPROTECT: likely too costly to unwind protect every elt
    RAW(data_)[length_] = value;
  } else {
    data_p_[length_] = value;
  }
  ++length_;
}

typedef r_vector<uint8_t> raws;

}  // namespace writable

}  // namespace cpp11
