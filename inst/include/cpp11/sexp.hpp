#pragma once

#include <stddef.h>  // for size_t

#include <string>  // for string, basic_string

#include "cpp11/R.hpp"                // for SEXP, SEXPREC, REAL_ELT, R_NilV...
#include "cpp11/attribute_proxy.hpp"  // for attribute_proxy
#include "cpp11/protect.hpp"          // for preserved

namespace cpp11 {

/// Converting to SEXP
class sexp {
 private:
  SEXP data_ = R_NilValue;
  SEXP preserve_token_ = R_NilValue;

 public:
  sexp() = default;

  sexp(SEXP data) : data_(data), preserve_token_(preserved.insert(data_)) {
    // REprintf("created %p %p\n", reinterpret_cast<void*>(data_),
    //          reinterpret_cast<void*>(preserve_token_));
  }

  sexp(const sexp& rhs) {
    data_ = rhs.data_;
    preserve_token_ = preserved.insert(data_);
    // REprintf("copied %p new protect %p\n", reinterpret_cast<void*>(rhs.data_),
    //          reinterpret_cast<void*>(preserve_token_));
  }

  sexp(sexp&& rhs) {
    data_ = rhs.data_;
    preserve_token_ = rhs.preserve_token_;

    rhs.data_ = R_NilValue;
    rhs.preserve_token_ = R_NilValue;

    // REprintf("moved %p\n", reinterpret_cast<void*>(rhs.data_));
  }

  sexp& operator=(const sexp& rhs) {
    preserved.release(preserve_token_);

    data_ = rhs.data_;
    preserve_token_ = preserved.insert(data_);
    // REprintf("assigned %p\n", reinterpret_cast<void*>(rhs.data_));
    return *this;
  }

  // void swap(sexp& rhs) {
  // sexp tmp(rhs);
  // rhs = *this;
  //*this = tmp;
  //}

  ~sexp() { preserved.release(preserve_token_); }

  attribute_proxy<sexp> attr(const char* name) const {
    return attribute_proxy<sexp>(*this, name);
  }

  attribute_proxy<sexp> attr(const std::string& name) const {
    return attribute_proxy<sexp>(*this, name.c_str());
  }

  attribute_proxy<sexp> attr(SEXP name) const {
    return attribute_proxy<sexp>(*this, name);
  }

  attribute_proxy<sexp> names() const {
    return attribute_proxy<sexp>(*this, R_NamesSymbol);
  }

  operator SEXP() const { return data_; }
  operator double() const { return REAL_ELT(data_, 0); }
  operator size_t() const { return REAL_ELT(data_, 0); }
  operator bool() const { return LOGICAL_ELT(data_, 0); }
  SEXP data() const { return data_; }
};

}  // namespace cpp11
