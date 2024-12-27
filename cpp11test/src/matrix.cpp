#include "cpp11/matrix.hpp"
#include "Rmath.h"
#include "cpp11/doubles.hpp"
using namespace cpp11;

[[cpp11::register]] SEXP gibbs_cpp(int N, int thin) {
  cpp11::writable::doubles_matrix<> mat(N, 2);
  double x = 0, y = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < thin; j++) {
      x = Rf_rgamma(3., 1. / double(y * y + 4));
      y = Rf_rnorm(1. / (x + 1.), 1. / sqrt(2. * (x + 1.)));
      // REprintf("x: %f y: %f\n", x, y);
    }
    mat[i][0] = x;
    mat[i][1] = y;
  }
  return mat;
}

[[cpp11::register]] cpp11::doubles_matrix<> gibbs_cpp2(int N, int thin) {
  cpp11::writable::doubles_matrix<> mat(N, 2);
  double x = 0, y = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < thin; j++) {
      x = Rf_rgamma(3., 1. / double(y * y + 4));
      y = Rf_rnorm(1. / (x + 1.), 1. / sqrt(2. * (x + 1.)));
    }
    mat(i, 0) = x;
    mat(i, 1) = y;
  }
  return mat;
}

#include <Rcpp.h>
using namespace Rcpp;

[[cpp11::register]] NumericMatrix gibbs_rcpp(int N, int thin) {
  NumericMatrix mat(N, 2);
  double x = 0, y = 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < thin; j++) {
      x = rgamma(1, 3, 1 / (y * y + 4))[0];
      y = rnorm(1, 1 / (x + 1), 1 / sqrt(2 * (x + 1)))[0];
    }
    mat(i, 0) = x;
    mat(i, 1) = y;
  }

  return (mat);
}

[[cpp11::register]] NumericMatrix gibbs_rcpp2(int N, int thin) {
  NumericMatrix mat(N, 2);
  double x = 0, y = 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < thin; j++) {
      x = Rf_rgamma(3., 1. / (y * y + 4));
      y = Rf_rnorm(1. / (x + 1), 1 / sqrt(2 * (x + 1)));
    }
    mat(i, 0) = x;
    mat(i, 1) = y;
  }

  return (mat);
}

[[cpp11::register]] cpp11::doubles row_sums(cpp11::doubles_matrix<cpp11::by_row> x) {
  cpp11::writable::doubles sums(x.nrow());

  int i = 0;
  for (auto row : x) {
    sums[i] = 0.;
    for (auto&& val : row) {
      if (cpp11::is_na(val)) {
        sums[i] = NA_REAL;
        break;
      }
      sums[i] += val;
    }
    ++i;
  }

  return sums;
}

[[cpp11::register]] cpp11::doubles col_sums(cpp11::doubles_matrix<cpp11::by_column> x) {
  cpp11::writable::doubles sums(x.ncol());

  int i = 0;
  for (auto col : x) {
    sums[i] = 0.;
    for (auto&& val : col) {
      if (cpp11::is_na(val)) {
        sums[i] = NA_REAL;
        break;
      }
      sums[i] += val;
    }
    ++i;
  }

  return sums;
}

[[cpp11::register]] cpp11::doubles_matrix<> log_mat_mat(cpp11::doubles_matrix<> x) {
  cpp11::writable::doubles_matrix<> out(x.nrow(), x.ncol());

  for (int i = 0; i < x.nrow(); i++) {
    for (int j = 0; j < x.ncol(); j++) {
      out(i, j) = log(x(i, j));
    }
  }

  // SEXP dimnames = x.attr("dimnames");
  // if (dimnames != R_NilValue) {
  //   Rf_setAttrib(out.data(), R_DimNamesSymbol, dimnames);
  //   std::cout << "dimnames set successfully" << std::endl;
  // }

  out.attr("dimnames") = x.attr("dimnames");

  return out;
}

[[cpp11::register]] SEXP log_mat_sexp(cpp11::doubles_matrix<> x) {
  cpp11::writable::doubles_matrix<> out(x.nrow(), x.ncol());

  for (int i = 0; i < x.nrow(); i++) {
    for (int j = 0; j < x.ncol(); j++) {
      out(i, j) = log(x(i, j));
    }
  }

  // SEXP dimnames = x.attr("dimnames");
  // if (dimnames != R_NilValue) {
  //   Rf_setAttrib(out.data(), R_DimNamesSymbol, dimnames);
  // }

  out.attr("dimnames") = x.attr("dimnames");

  return out;
}
