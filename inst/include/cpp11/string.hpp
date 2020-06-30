#pragma once

#include <string>
#include "cpp11/R.hpp"  // for SEXP, SEXPREC, Rf_translateCharUTF8

#include "R_ext/Memory.h"     // for vmaxget, vmaxset
#include "cpp11/protect.hpp"  // for unwind_protect, protect, protect::fun...
#include "cpp11/sexp.hpp"

namespace cpp11 {

class string {
 public:
  string() = default;
  string(SEXP data) : data_(data) {}
  string(const char* data) : data_(safe[Rf_mkCharCE](data, CE_UTF8)) {}

  operator SEXP() const { return data_; }
  operator std::string() const {
    void* vmax = vmaxget();
    std::string res;
    unwind_protect([&] { res = Rf_translateCharUTF8(data_); });
    vmaxset(vmax);
    return res;
  }

  bool operator==(const string& rhs) const { return data_.data() == rhs.data_.data(); }

  bool operator==(const SEXP& rhs) const { return data_.data() == rhs; }

  bool operator==(const char* rhs) const {
    return static_cast<std::string>(*this) == rhs;
  }

  R_xlen_t size() const { return Rf_xlength(data_); }

 private:
  sexp data_ = R_NilValue;
};  // namespace cpp11

/* This will translate the string to UTF-8, but I think that is actually the
 * right thing to do */
template <typename T>
using is_convertible_to_cpp11_string =
    typename std::enable_if<std::is_convertible<T, cpp11::string>::value &&
                                !std::is_convertible<T, const char*>::value,
                            T>::type;

template <typename T, is_convertible_to_cpp11_string<T>* = nullptr>
inline SEXP as_sexp(T from) {
  return as_sexp({static_cast<std::string>(from)});
}

}  // namespace cpp11
