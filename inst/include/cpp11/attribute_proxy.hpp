#pragma once

#include <initializer_list>  // for initializer_list
#include "cpp11/R.hpp"
#include "cpp11/as.hpp"  // for as_sexp, is_vector_of_strings
#include "cpp11/protect.hpp"

namespace cpp11 {

class sexp;

template <typename T>
class attribute_proxy {
 private:
  const T& parent_;
  SEXP symbol_;

 public:
  attribute_proxy(const T& parent, const char* index)
      : parent_(parent), symbol_(safe[Rf_install](index)) {}

  attribute_proxy(const T& parent, SEXP index) : parent_(parent), symbol_(index) {}

  template <typename C>
  attribute_proxy& operator=(C rhs) {
    // NOPROTECT: Rf_setAttrib with a SYMSXP does not allocate
    Rf_setAttrib(parent_.data(), symbol_, as_sexp(rhs));
    return *this;
  }

  template <typename C>
  attribute_proxy& operator=(std::initializer_list<C> rhs) {
    // NOPROTECT: Rf_setAttrib with a SYMSXP does not allocate
    Rf_setAttrib(parent_.data(), symbol_, as_sexp(rhs));
    return *this;
  }

  operator SEXP() const { return safe[Rf_getAttrib](parent_.data(), symbol_); }
};

}  // namespace cpp11
