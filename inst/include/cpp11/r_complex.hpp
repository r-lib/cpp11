#pragma once

#include <complex>  // for complex
#include <ostream>
#include <type_traits>  // for is_convertible, enable_if

#include "R_ext/Arith.h"       // for NA_REAL
#include "R_ext/Complex.h"     // for Rcomplex
#include "cpp11/R.hpp"         // for SEXP, SEXPREC, ...
#include "cpp11/as.hpp"        // for as_sexp
#include "cpp11/protect.hpp"   // for unwind_protect, preserved
#include "cpp11/r_vector.hpp"  // for r_vector
#include "cpp11/sexp.hpp"      // for sexp

namespace cpp11 {

class r_complex {
 public:
  r_complex() : r_(NA_REAL), i_(NA_REAL) {}
  r_complex(double r, double i) : r_(r), i_(i) {}
  r_complex(const std::complex<double>& c) : r_(c.real()), i_(c.imag()) {}
  r_complex(const Rcomplex& rc) : r_(rc.r), i_(rc.i) {}

  double real() const { return r_; }
  double imag() const { return i_; }

  operator std::complex<double>() const { return std::complex<double>(r_, i_); }
  operator Rcomplex() const { return {r_, i_}; }

  bool operator==(const r_complex& other) const {
    return r_ == other.r_ && i_ == other.i_;
  }

 private:
  double r_;
  double i_;
};

// Specialization for r_complex
template <>
inline void writable::r_vector<r_complex>::push_back(r_complex value) {
  while (this->length_ >= this->capacity_) {
    this->reserve(this->capacity_ == 0 ? 1 : this->capacity_ * 2);
  }

  if (this->data_p_ != nullptr) {
    this->data_p_[this->length_] = static_cast<Rcomplex>(value);
  } else {
    set_elt(this->data_, this->length_, value);
  }

  ++this->length_;
}

// Specialization for std::complex<double>
template <>
inline void writable::r_vector<r_complex>::push_back(const std::complex<double>& value) {
  this->push_back(r_complex(value.real(), value.imag()));
}

}  // namespace cpp11
