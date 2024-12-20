#include <numeric>
#include "cpp11/complexes.hpp"
#include "cpp11/doubles.hpp"

[[cpp11::register]] double sum_dbl_for_(cpp11::doubles x) {
  double sum = 0.;
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum += x[i];
  }

  return sum;
}

[[cpp11::register]] double sum_dbl_for2_(SEXP x_sxp) {
  double sum = 0.;
  const cpp11::doubles x(x_sxp, false);
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum += x[i];
  }

  return sum;
}

[[cpp11::register]] double sum_dbl_for3_(SEXP x_sxp) {
  double sum = 0.;
  const cpp11::writable::doubles x(x_sxp, false);
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum += x[i];
  }

  return sum;
}

[[cpp11::register]] double sum_dbl_foreach_(cpp11::doubles x) {
  double sum = 0.;
  for (const auto&& val : x) {
    sum += val;
  }
  return sum;
}

[[cpp11::register]] double sum_dbl_foreach2_(SEXP x_sxp) {
  const cpp11::doubles x(x_sxp, false);
  double sum = 0.;
  for (const auto&& val : x) {
    sum += val;
  }
  return sum;
}

[[cpp11::register]] double sum_dbl_accumulate_(cpp11::doubles x) {
  return std::accumulate(x.cbegin(), x.cend(), 0.);
}

[[cpp11::register]] double sum_dbl_accumulate2_(SEXP x_sxp) {
  const cpp11::doubles x(x_sxp, false);
  return std::accumulate(x.cbegin(), x.cend(), 0.);
}

// Functions for complex data type

[[cpp11::register]] cpp11::r_complex sum_cplx_for_(cpp11::complexes x) {
  std::complex<double> sum = {0.0, 0.0};
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum.real(sum.real() + x[i].real());
    sum.imag(sum.imag() + x[i].imag());
  }

  return cpp11::r_complex(sum.real(), sum.imag());
}

[[cpp11::register]] cpp11::complexes sum_cplx_for_2_(cpp11::complexes x) {
  std::complex<double> sum = {0.0, 0.0};
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum.real(sum.real() + x[i].real());
    sum.imag(sum.imag() + x[i].imag());
  }

  cpp11::writable::complexes result(1);
  result[0] = cpp11::r_complex(sum.real(), sum.imag());
  return result;
}

[[cpp11::register]] std::complex<double> sum_cplx_for_3_(cpp11::complexes x_sxp) {
  std::complex<double> sum = {0.0, 0.0};
  const cpp11::complexes x(x_sxp, false);
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum.real(sum.real() + x[i].real());
    sum.imag(sum.imag() + x[i].imag());
  }

  return sum;
}

[[cpp11::register]] std::complex<double> sum_cplx_for_4_(SEXP x_sxp) {
  std::complex<double> sum = {0.0, 0.0};
  const cpp11::complexes x(x_sxp, false);
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum.real(sum.real() + x[i].real());
    sum.imag(sum.imag() + x[i].imag());
  }

  return sum;
}

[[cpp11::register]] SEXP sum_cplx_for_5_(SEXP x_sxp) {
  std::complex<double> sum = {0.0, 0.0};
  const cpp11::complexes x(x_sxp, false);
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum.real(sum.real() + x[i].real());
    sum.imag(sum.imag() + x[i].imag());
  }

  return cpp11::as_sexp(sum);
}

[[cpp11::register]] cpp11::complexes sum_cplx_for_6_(SEXP x_sxp) {
  std::complex<double> sum = {0.0, 0.0};
  const cpp11::complexes x(x_sxp, false);
  R_xlen_t n = x.size();
  for (R_xlen_t i = 0; i < n; ++i) {
    sum.real(sum.real() + x[i].real());
    sum.imag(sum.imag() + x[i].imag());
  }

  return cpp11::as_sexp(sum);
}
