#pragma once

#include "cpp11/R.hpp"
#include "cpp11/r_vector.hpp"
#include "cpp11/sexp.hpp"

// dgeMatrix: Class "dgeMatrix" of Dense Numeric (S4 Class) Matrices

namespace cpp11 {

template <typename S = by_column>
class dge_matrix {
 private:
  writable::r_vector<double> vector_;
  int nrow_;
  int ncol_;

 public:
  dge_matrix(SEXP data) {
    SEXP x_slot = R_do_slot(data, Rf_install("x"));

    // get dimensions

    // nrow_ = Rf_nrows(data);
    // ncol_ = Rf_ncols(data);

    // use attr instead (Matrix != matrix class)
    SEXP dim = R_do_slot(data, Rf_install("Dim"));
    nrow_ = INTEGER(dim)[0];
    ncol_ = INTEGER(dim)[1];

    if (nrow_ <= 0 || ncol_ <= 0) {
      throw std::runtime_error("Invalid matrix dimensions");
    }

    vector_ = writable::r_vector<double>(Rf_allocVector(REALSXP, Rf_length(x_slot)));
    for (int i = 0; i < Rf_length(x_slot); ++i) {
      vector_[i] = REAL(x_slot)[i];
    }

    SEXP dims = PROTECT(Rf_allocVector(INTSXP, 2));
    INTEGER(dims)[0] = nrow_;
    INTEGER(dims)[1] = ncol_;
    vector_.attr(R_DimSymbol) = dims;
    UNPROTECT(1);
  }

  int nrow() const { return nrow_; }
  int ncol() const { return ncol_; }

  double operator()(int row, int col) const { return vector_[row + (col * nrow_)]; }
};

namespace writable {
template <typename S = by_column>
using dge_matrix = cpp11::dge_matrix<S>;
}  // namespace writable

}  // namespace cpp11

// dsyMatrix: Symmetric Dense (Packed or Unpacked) Numeric Matrices

namespace cpp11 {

template <typename S = by_column>
class dsy_matrix {
 private:
  writable::r_vector<double> vector_;
  int nrow_;
  int ncol_;
  bool is_packed_;
  bool is_upper_;

 public:
  dsy_matrix(SEXP data) {
    SEXP x_slot = R_do_slot(data, Rf_install("x"));

    // use attr instead (Matrix != matrix class)
    SEXP dim = R_do_slot(data, Rf_install("Dim"));
    nrow_ = INTEGER(dim)[0];
    ncol_ = INTEGER(dim)[1];

    if (nrow_ <= 0 || ncol_ <= 0) {
      throw std::runtime_error("Invalid matrix dimensions");
    }

    // Check if the matrix is packed and if it's upper or lower triangular
    SEXP uplo = R_do_slot(data, Rf_install("uplo"));
    is_upper_ = (Rf_asChar(uplo) == Rf_mkChar("U"));
    is_packed_ = (Rf_length(x_slot) == (nrow_ * (nrow_ + 1)) / 2);

    vector_ = writable::r_vector<double>(Rf_allocVector(REALSXP, Rf_length(x_slot)));
    for (int i = 0; i < Rf_length(x_slot); ++i) {
      vector_[i] = REAL(x_slot)[i];
    }

    SEXP dims = PROTECT(Rf_allocVector(INTSXP, 2));
    INTEGER(dims)[0] = nrow_;
    INTEGER(dims)[1] = ncol_;
    vector_.attr(R_DimSymbol) = dims;
    UNPROTECT(1);
  }

  int nrow() const { return nrow_; }
  int ncol() const { return ncol_; }

  double operator()(int row, int col) const {
    if (is_packed_) {
      if (is_upper_) {
        if (row <= col) {
          return vector_[col * (col + 1) / 2 + row];
        } else {
          return vector_[row * (row + 1) / 2 + col];
        }
      } else {
        if (row >= col) {
          return vector_[row * (row + 1) / 2 + col];
        } else {
          return vector_[col * (col + 1) / 2 + row];
        }
      }
    } else {
      return vector_[row + (col * nrow_)];
    }
  }
};

namespace writable {
template <typename S = by_column>
using dsy_matrix = cpp11::dsy_matrix<S>;
}  // namespace writable

}  // namespace cpp11
