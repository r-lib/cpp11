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
inline SEXP r_vector<r_bool>::valid_type(SEXP data) {
  if (data == nullptr) {
    throw type_error(LGLSXP, NILSXP);
  }
  if (TYPEOF(data) != LGLSXP) {
    throw type_error(LGLSXP, TYPEOF(data));
  }
  return data;
}

template <>
inline r_bool r_vector<r_bool>::operator[](const R_xlen_t pos) const {
  return is_altrep_ ? LOGICAL_ELT(data_, pos) : data_p_[pos];
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
inline void r_vector<r_bool>::const_iterator::fill_buf(R_xlen_t pos) {
  length_ = std::min(64_xl, data_->size() - pos);
  LOGICAL_GET_REGION(data_->data_, pos, length_, buf_.data());
  block_start_ = pos;
}

typedef r_vector<r_bool> logicals;

namespace writable {

template <>
inline SEXPTYPE r_vector<r_bool>::get_sexptype() {
  return LGLSXP;
}

template <>
inline void r_vector<r_bool>::set_elt(
    SEXP x, R_xlen_t i, typename traits::get_underlying_type<r_bool>::type value) {
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

template <>
inline r_vector<r_bool>::proxy::operator r_bool() const {
  if (p_ == nullptr) {
    return LOGICAL_ELT(data_, index_);
  } else {
    return *p_;
  }
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

template <>
inline void r_vector<r_bool>::push_back(r_bool value) {
  while (length_ >= capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ *= 2);
  }
  if (is_altrep_) {
    SET_LOGICAL_ELT(data_, length_, value);
  } else {
    data_p_[length_] = value;
  }
  ++length_;
}

typedef r_vector<r_bool> logicals;

}  // namespace writable

}  // namespace cpp11
