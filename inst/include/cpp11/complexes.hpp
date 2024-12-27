#pragma once

#include <algorithm>         // for std::transform
#include <complex>           // for std::complex
#include <initializer_list>  // for std::initializer_list

#include "cpp11/R.hpp"  // for SEXP, SEXPREC, Rf_allocVector, COMPLEX, COMPLEX_ELT, SET_COMPLEX_ELT
#include "cpp11/as.hpp"         // for as_sexp
#include "cpp11/protect.hpp"    // for safe
#include "cpp11/r_complex.hpp"  // for r_complex
#include "cpp11/r_vector.hpp"   // for r_vector, r_vector<>::proxy
#include "cpp11/sexp.hpp"       // for sexp

namespace cpp11 {

// Specializations for complex numbers

template <>
inline SEXPTYPE r_vector<r_complex>::get_sexptype() {
  return CPLXSXP;
}

template <>
inline typename r_vector<r_complex>::underlying_type r_vector<r_complex>::get_elt(
    SEXP x, R_xlen_t i) {
  return COMPLEX_ELT(x, i);
}

template <>
inline typename r_vector<r_complex>::underlying_type* r_vector<r_complex>::get_p(
    bool is_altrep, SEXP data) {
  if (is_altrep) {
    return nullptr;
  } else {
    return COMPLEX(data);
  }
}

template <>
inline typename r_vector<r_complex>::underlying_type const*
r_vector<r_complex>::get_const_p(bool is_altrep, SEXP data) {
  return COMPLEX_OR_NULL(data);
}

template <>
inline void r_vector<r_complex>::get_region(SEXP x, R_xlen_t i, R_xlen_t n,
                                            typename r_vector::underlying_type* buf) {
  COMPLEX_GET_REGION(x, i, n, buf);
}

template <>
inline bool r_vector<r_complex>::const_iterator::use_buf(bool is_altrep) {
  return is_altrep;
}

typedef r_vector<r_complex> complexes;

namespace writable {

template <>
inline void r_vector<r_complex>::set_elt(
    SEXP x, R_xlen_t i, typename cpp11::r_vector<r_complex>::underlying_type value) {
  COMPLEX(x)[i] = value;
}

typedef r_vector<r_complex> complexes;

}  // namespace writable

inline complexes as_complexes(SEXP x) {
  if (detail::r_typeof(x) == CPLXSXP) {
    return complexes(x);
  }

  else if (detail::r_typeof(x) == INTSXP) {
    r_vector<int> xn(x);
    size_t len = xn.size();
    writable::complexes ret(len);
    std::transform(xn.begin(), xn.end(), ret.begin(), [](int value) {
      return value == NA_INTEGER ? r_complex(NA_REAL, NA_REAL)
                                 : r_complex(static_cast<double>(value), 0.0);
    });
    return ret;
  }

  throw type_error(CPLXSXP, detail::r_typeof(x));
}

// Define comparison operators within the proxy class
namespace writable {

template <>
class r_vector<r_complex>::proxy {
 public:
  proxy(SEXP data, R_xlen_t index)
      : data_(data), index_(index), buf_(nullptr), is_altrep_(false) {}

  proxy(SEXP data, R_xlen_t index, Rcomplex* buf, bool is_altrep)
      : data_(data), index_(index), buf_(buf), is_altrep_(is_altrep) {}

  operator r_complex() const {
    if (is_altrep_ && buf_ != nullptr) {
      return r_complex(buf_->r, buf_->i);
    } else {
      Rcomplex r = COMPLEX_ELT(data_, index_);
      return r_complex(r.r, r.i);
    }
  }

  proxy& operator=(const r_complex& value) {
    if (is_altrep_ && buf_ != nullptr) {
      buf_->r = value.real();
      buf_->i = value.imag();
    } else {
      Rcomplex r;
      r.r = value.real();
      r.i = value.imag();
      SET_COMPLEX_ELT(data_, index_, r);
    }
    return *this;
  }

  proxy& operator=(const std::complex<double>& value) {
    if (is_altrep_ && buf_ != nullptr) {
      buf_->r = value.real();
      buf_->i = value.imag();
    } else {
      Rcomplex r;
      r.r = value.real();
      r.i = value.imag();
      SET_COMPLEX_ELT(data_, index_, r);
    }
    return *this;
  }

  proxy& operator+=(const r_complex& value) {
    *this = static_cast<r_complex>(*this) + value;
    return *this;
  }

  proxy& operator-=(const r_complex& value) {
    *this = static_cast<r_complex>(*this) - value;
    return *this;
  }

  proxy& operator*=(const r_complex& value) {
    *this = static_cast<r_complex>(*this) * value;
    return *this;
  }

  proxy& operator/=(const r_complex& value) {
    *this = static_cast<r_complex>(*this) / value;
    return *this;
  }

  proxy& operator++() {
    *this += r_complex(1, 0);
    return *this;
  }

  proxy operator++(int) {
    proxy tmp(*this);
    operator++();
    return tmp;
  }

  proxy& operator--() {
    *this -= r_complex(1, 0);
    return *this;
  }

  proxy operator--(int) {
    proxy tmp(*this);
    operator--();
    return tmp;
  }

  friend bool operator==(const proxy& lhs, const r_complex& rhs) {
    return static_cast<r_complex>(lhs) == rhs;
  }

  friend bool operator!=(const proxy& lhs, const r_complex& rhs) { return !(lhs == rhs); }

 private:
  SEXP data_;
  R_xlen_t index_;
  Rcomplex* buf_;
  bool is_altrep_;
};

}  // namespace writable

// New complex_vector class for handling complex numbers in SEXP
class complex_vector {
 public:
  explicit complex_vector(SEXP x)
      : data_(reinterpret_cast<Rcomplex*>(DATAPTR(x))), size_(Rf_length(x)) {}

  std::complex<double> operator[](R_xlen_t i) const { return {data_[i].r, data_[i].i}; }

  size_t size() const { return size_; }

 private:
  Rcomplex* data_;
  size_t size_;
};

// Template specialization for adding cpp11::r_complex to std::complex<double>
template <typename T>
inline std::complex<T>& operator+=(std::complex<T>& lhs, const cpp11::r_complex& rhs) {
  lhs.real(lhs.real() + rhs.real());
  lhs.imag(lhs.imag() + rhs.imag());
  return lhs;
}

// Add constructor for initializer_list
template <>
inline r_vector<r_complex>::r_vector(std::initializer_list<r_complex> il) {
  R_xlen_t size = il.size();
  SEXP data = PROTECT(Rf_allocVector(CPLXSXP, size));
  auto it = il.begin();
  for (R_xlen_t i = 0; i < size; ++i, ++it) {
    Rcomplex r;
    r.r = it->real();
    r.i = it->imag();
    COMPLEX(data)[i] = r;
  }
  UNPROTECT(1);
  data_ = data;
}

// Comparison operators for r_vector<r_complex>
template <>
inline bool operator==(const r_vector<r_complex>& lhs, const r_vector<r_complex>& rhs) {
  if (lhs.size() != rhs.size()) return false;
  for (R_xlen_t i = 0; i < lhs.size(); ++i) {
    if (!(lhs[i] == rhs[i])) return false;
  }
  return true;
}

template <>
inline bool operator!=(const r_vector<r_complex>& lhs, const r_vector<r_complex>& rhs) {
  return !(lhs == rhs);
}

}  // namespace cpp11
