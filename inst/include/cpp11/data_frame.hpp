#pragma once

#include <cstdlib>           // for abs
#include <initializer_list>  // for initializer_list
#include <string>            // for string, basic_string
#include <utility>           // for move

#include "R_ext/Arith.h"              // for NA_INTEGER
#include "cpp11/R.hpp"                // for Rf_xlength, SEXP, SEXPREC, INTEGER
#include "cpp11/attribute_proxy.hpp"  // for attribute_proxy
#include "cpp11/list.hpp"             // for list, r_vector<>::r_vector, r_v...
#include "cpp11/r_vector.hpp"         // for r_vector

namespace cpp11 {

class named_arg;
namespace writable {
class data_frame;
}  // namespace writable

class data_frame : public list {
  using list::list;

  friend class writable::data_frame;

  static R_xlen_t calculate_nrow(SEXP x) {
    // If there is a `R_RowNamesSymbol`, we take the number of rows from there
    // (regardless of whether or not there is a `"data.frame"` class yet!).
    //
    // As of R >=3.5, `Rf_getAttrib(R_RowNamesSymbol)` returns one of the following:
    // - A character vector
    // - An integer vector
    // - An ALTREP integer compact intrange (converted cheaply from `c(NA, -n)`)
    //
    // We can take the `Rf_xlength()` of all of these cheaply.
    //
    // We used to worry about `Rf_getAttrib()` fully expanding `c(NA, -n)`, but with
    // ALTREP integer compact intranges that is no longer the case.
    SEXP row_names = Rf_getAttrib(x, R_RowNamesSymbol);
    if (row_names != R_NilValue) {
      return Rf_xlength(row_names);
    }

    // Otherwise it's a bare list, and we infer the number of rows from the first element
    // (i.e. first column). Calling `Rf_xlength()` on the first column isn't 100% right
    // (it doesn't dispatch to `length()`, nor does it correctly handle df-cols or
    // matrix-cols), but it is close enough and people can use the data_frame constructor
    // that allows you to specify `nrow` directly as needed.
    if (Rf_xlength(x) == 0) {
      return 0;
    } else {
      return Rf_xlength(VECTOR_ELT(x, 0));
    }
  }

 public:
  R_xlen_t nrow() const { return calculate_nrow(*this); }
  R_xlen_t ncol() const { return size(); }
};

namespace writable {
class data_frame : public cpp11::data_frame {
 private:
  writable::list set_data_frame_attributes(writable::list&& x) {
    return set_data_frame_attributes(std::move(x), calculate_nrow(x));
  }

  writable::list set_data_frame_attributes(writable::list&& x, R_xlen_t nrow) {
    // `Rf_setAttrib(R_RowNamesSymbol)` will keep `c(NA, -n)` in compact form
    x.attr(R_RowNamesSymbol) = {NA_INTEGER, -static_cast<int>(nrow)};
    x.attr(R_ClassSymbol) = "data.frame";
    return std::move(x);
  }

 public:
  data_frame(const SEXP data) : cpp11::data_frame(set_data_frame_attributes(data)) {}
  data_frame(const SEXP data, bool is_altrep)
      : cpp11::data_frame(set_data_frame_attributes(data), is_altrep) {}
  data_frame(const SEXP data, bool is_altrep, R_xlen_t nrow)
      : cpp11::data_frame(set_data_frame_attributes(data, nrow), is_altrep) {}
  data_frame(std::initializer_list<list> il)
      : cpp11::data_frame(set_data_frame_attributes(writable::list(il))) {}
  data_frame(std::initializer_list<named_arg> il)
      : cpp11::data_frame(set_data_frame_attributes(writable::list(il))) {}

  using cpp11::data_frame::ncol;
  using cpp11::data_frame::nrow;

  attribute_proxy<data_frame> attr(const char* name) const { return {*this, name}; }

  attribute_proxy<data_frame> attr(const std::string& name) const {
    return {*this, name.c_str()};
  }

  attribute_proxy<data_frame> attr(SEXP name) const { return {*this, name}; }

  attribute_proxy<data_frame> names() const { return {*this, R_NamesSymbol}; }
};

}  // namespace writable

}  // namespace cpp11
