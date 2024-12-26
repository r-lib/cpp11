#pragma once

#include <complex>  // for complex
#include <ostream>
#include <type_traits>  // for is_convertible, enable_if

#include "R_ext/Arith.h"      // for NA_REAL
#include "R_ext/Complex.h"    // for Rcomplex
#include "cpp11/R.hpp"        // for SEXP, SEXPREC, ...
#include "cpp11/as.hpp"       // for as_sexp
#include "cpp11/protect.hpp"  // for unwind_protect, preserved
#include "cpp11/sexp.hpp"     // for sexp

namespace cpp11 {

class r_complex {
 public:
  r_complex() = default;

  r_complex(SEXP data) {
    if (Rf_isComplex(data) && Rf_xlength(data) == 1) {
      Rcomplex elt = COMPLEX_ELT(data, 0);
      real_ = elt.r;
      imag_ = elt.i;
    } else {
      throw std::invalid_argument("Invalid r_complex value");
    }
  }

  r_complex(double real, double imag) : real_(real), imag_(imag) {}

  explicit r_complex(Rcomplex value) : real_(value.r), imag_(value.i) {}
  explicit r_complex(std::complex<double> value)
      : real_(value.real()), imag_(value.imag()) {}

  explicit operator Rcomplex() const { return Rcomplex{real_, imag_}; }
  explicit operator std::complex<double>() const {
    return std::complex<double>(real_, imag_);
  }

  double real() const { return real_; }
  double imag() const { return imag_; }

  r_complex& operator+=(const r_complex& other) {
    real_ += other.real_;
    imag_ += other.imag_;
    return *this;
  }

  r_complex& operator-=(const r_complex& other) {
    real_ -= other.real_;
    imag_ -= other.imag_;
    return *this;
  }

  r_complex& operator*=(const r_complex& other) {
    double r = real_ * other.real_ - imag_ * other.imag_;
    double i = real_ * other.imag_ + imag_ * other.real_;
    real_ = r;
    imag_ = i;
    return *this;
  }

  r_complex& operator/=(const r_complex& other) {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    double r = (real_ * other.real_ + imag_ * other.imag_) / denom;
    double i = (imag_ * other.real_ - real_ * other.imag_) / denom;
    real_ = r;
    imag_ = i;
    return *this;
  }

 private:
  double real_;
  double imag_;
};

inline r_complex operator+(r_complex lhs, const r_complex& rhs) {
  lhs += rhs;
  return lhs;
}

inline r_complex operator-(r_complex lhs, const r_complex& rhs) {
  lhs -= rhs;
  return lhs;
}

inline r_complex operator*(r_complex lhs, const r_complex& rhs) {
  lhs *= rhs;
  return lhs;
}

inline r_complex operator/(r_complex lhs, const r_complex& rhs) {
  lhs /= rhs;
  return lhs;
}

inline bool operator==(const r_complex& x, const r_complex& y) {
  return (x.real() == y.real()) && (x.imag() == y.imag());
}

inline std::ostream& operator<<(std::ostream& os, const r_complex& value) {
  os << value.real() << "+" << value.imag() << "i";
  return os;
}

template <>
inline r_complex na() {
  return r_complex(NA_REAL, NA_REAL);
}

template <>
inline bool is_na(const r_complex& x) {
  return ISNA(x.real()) || ISNA(x.imag());
}

template <typename T>
struct is_r_complex : std::false_type {};

template <>
struct is_r_complex<r_complex> : std::true_type {};

template <typename T, typename R = void>
using enable_if_r_complex = std::enable_if_t<is_r_complex<T>::value, R>;

template <typename T>
enable_if_r_complex<T, SEXP> as_sexp(T from) {
  SEXP res = PROTECT(Rf_allocVector(CPLXSXP, 1));
  Rcomplex* r = COMPLEX(res);
  r[0].r = from.real();
  r[0].i = from.imag();
  UNPROTECT(1);
  return res;
}

namespace traits {
template <>
struct get_underlying_type<r_complex> {
  using type = Rcomplex;
};
}  // namespace traits

// Define operator+ for std::complex<double> and r_complex
inline std::complex<double> operator+(const std::complex<double>& lhs,
                                      const r_complex& rhs) {
  return std::complex<double>(lhs.real() + rhs.real(), lhs.imag() + rhs.imag());
}

inline std::complex<double> operator+(const r_complex& lhs,
                                      const std::complex<double>& rhs) {
  return std::complex<double>(lhs.real() + rhs.real(), lhs.imag() + rhs.imag());
}

}  // namespace cpp11
