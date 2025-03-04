#pragma once

#include <complex>  // for std::complex

#include "cpp11/R.hpp"        // for SEXP, SEXPREC, Rf_mkCharCE, Rf_translateCharUTF8
#include "cpp11/as.hpp"       // for as_sexp
#include "cpp11/protect.hpp"  // for unwind_protect, protect, protect::function
#include "cpp11/sexp.hpp"     // for sexp

namespace cpp11 {

class r_complex {
 public:
  r_complex() : data_(safe[Rf_allocVector](CPLXSXP, 1)) {
    COMPLEX(data_)[0].r = 0;
    COMPLEX(data_)[0].i = 0;
  }
  r_complex(SEXP data) : data_(data) {
    if (data_ == R_NilValue) {
      data_ = PROTECT(Rf_allocVector(CPLXSXP, 0));
      UNPROTECT(1);
    }
  }
  r_complex(double real, double imag) : data_(safe[Rf_allocVector](CPLXSXP, 1)) {
    COMPLEX(data_)[0].r = real;
    COMPLEX(data_)[0].i = imag;
  }
  r_complex(const std::complex<double>& data) : r_complex(data.real(), data.imag()) {}
  r_complex(const Rcomplex& data) : r_complex(data.r, data.i) {}

  operator SEXP() const { return data_; }
  operator sexp() const { return data_; }
  operator std::complex<double>() const {
    if (data_ == R_NilValue || Rf_length(data_) == 0) {
      return {NA_REAL, NA_REAL};
    }
    return {COMPLEX(data_)[0].r, COMPLEX(data_)[0].i};
  }
  operator Rcomplex() const {
    Rcomplex r;
    if (data_ == R_NilValue || Rf_length(data_) == 0) {
      r.r = NA_REAL;
      r.i = NA_REAL;
    } else {
      r.r = real();
      r.i = imag();
    }
    return r;
  }

  double real() const {
    if (data_ == R_NilValue || Rf_length(data_) == 0) {
      return NA_REAL;
    }
    return COMPLEX(data_)[0].r;
  }
  double imag() const {
    if (data_ == R_NilValue || Rf_length(data_) == 0) {
      return NA_REAL;
    }
    return COMPLEX(data_)[0].i;
  }

  bool operator==(const r_complex& rhs) const {
    return (is_na() && rhs.is_na()) || (real() == rhs.real() && imag() == rhs.imag());
  }

  bool operator!=(const r_complex& rhs) const { return !(*this == rhs); }

  r_complex& operator+=(const r_complex& rhs) {
    *this = r_complex(real() + rhs.real(), imag() + rhs.imag());
    return *this;
  }

  r_complex& operator-=(const r_complex& rhs) {
    *this = r_complex(real() - rhs.real(), imag() - rhs.imag());
    return *this;
  }

  r_complex& operator*=(const r_complex& rhs) {
    std::complex<double> lhs = *this;
    lhs *= static_cast<std::complex<double>>(rhs);
    *this = r_complex(lhs.real(), lhs.imag());
    return *this;
  }

  r_complex& operator/=(const r_complex& rhs) {
    std::complex<double> lhs = *this;
    lhs /= static_cast<std::complex<double>>(rhs);
    *this = r_complex(lhs.real(), lhs.imag());
    return *this;
  }

  friend r_complex operator+(r_complex lhs, const r_complex& rhs) {
    lhs += rhs;
    return lhs;
  }

  friend r_complex operator-(r_complex lhs, const r_complex& rhs) {
    lhs -= rhs;
    return lhs;
  }

  friend r_complex operator*(r_complex lhs, const r_complex& rhs) {
    lhs *= rhs;
    return lhs;
  }

  friend r_complex operator/(r_complex lhs, const r_complex& rhs) {
    lhs /= rhs;
    return lhs;
  }

  bool is_na() const { return R_IsNA(real()) || R_IsNA(imag()); }

 private:
  sexp data_ = R_NilValue;
};

inline SEXP as_sexp(const r_complex& from) {
  sexp res;
  unwind_protect([&] {
    res = Rf_allocVector(CPLXSXP, 1);
    COMPLEX(res)[0].r = from.real();
    COMPLEX(res)[0].i = from.imag();
  });

  return res;
}

inline SEXP as_sexp(std::initializer_list<r_complex> il) {
  R_xlen_t size = il.size();

  sexp data;
  unwind_protect([&] {
    data = Rf_allocVector(CPLXSXP, size);
    auto it = il.begin();
    for (R_xlen_t i = 0; i < size; ++i, ++it) {
      COMPLEX(data)[i].r = it->real();
      COMPLEX(data)[i].i = it->imag();
    }
  });
  return data;
}

template <>
inline r_complex na() {
  return r_complex(NA_REAL, NA_REAL);
}

namespace traits {
template <>
struct get_underlying_type<r_complex> {
  using type = Rcomplex;
};
}  // namespace traits

}  // namespace cpp11
