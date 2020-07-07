#pragma once

#include <string>             // for string, basic_string, operator==
#include <type_traits>        // for is_convertible, enable_if
#include "R_ext/Memory.h"     // for vmaxget, vmaxset
#include "cpp11/R.hpp"        // for SEXP, SEXPREC, Rf_mkCharCE, Rf_translat...
#include "cpp11/as.hpp"       // for as_sexp
#include "cpp11/protect.hpp"  // for unwind_protect, protect, protect::function
#include "cpp11/sexp.hpp"     // for sexp
namespace cpp11 {

class r_string {
 public:
  r_string() = default;
  r_string(SEXP data) : data_(data) {}
  r_string(const char* data) : data_(safe[Rf_mkCharCE](data, CE_UTF8)) {}
  r_string(const std::string& data) : data_(safe[Rf_mkCharCE](data.c_str(), CE_UTF8)) {}

  operator SEXP() const { return data_; }
  operator std::string() const {
    std::string res;
    res.reserve(size());

    void* vmax = vmaxget();
    unwind_protect([&] { res.assign(Rf_translateCharUTF8(data_)); });
    vmaxset(vmax);

    return res;
  }

  bool operator==(const r_string& rhs) const { return data_.data() == rhs.data_.data(); }

  bool operator==(const SEXP rhs) const { return data_.data() == rhs; }

  bool operator==(const char* rhs) const {
    return static_cast<std::string>(*this) == rhs;
  }

  bool operator==(const std::string& rhs) const {
    return static_cast<std::string>(*this) == rhs;
  }

  R_xlen_t size() const { return Rf_xlength(data_); }

 private:
  sexp data_ = R_NilValue;
};  // namespace cpp11

/* This will translate the r_string to UTF-8, but I think that is actually the
 * right thing to do */
template <typename T>
using is_convertible_to_cpp11_string =
    typename std::enable_if<std::is_convertible<T, cpp11::r_string>::value &&
                                !std::is_convertible<T, const char*>::value,
                            T>::type;

template <typename T, is_convertible_to_cpp11_string<T>* = nullptr>
inline SEXP as_sexp(T from) {
  return as_sexp({static_cast<std::string>(from)});
}

inline bool is_na(const r_string& x) { return x == NA_STRING; }
}  // namespace cpp11
