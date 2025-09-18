#include "cpp11/r_complex.hpp"

#include "cpp11/sexp.hpp"

#include <testthat.h>

context("r_complex-C++") {
  test_that("r_complex() zero initialization") {
    // `cpp11::r_complex x;` is "not initialized", this is "zero initialized"
    cpp11::r_complex x{};
    expect_true(x.real() == 0.);
    expect_true(x.imag() == 0.);
  }

  test_that("r_complex(double, double) and accessors") {
    cpp11::r_complex x(1., 2.);
    expect_true(x.real() == 1.);
    expect_true(x.imag() == 2.);
  }

  test_that("r_complex(SEXP)") {
    cpp11::r_complex x(1, 2);

    cpp11::sexp value = Rf_allocVector(CPLXSXP, 1);
    COMPLEX(value)[0] = static_cast<Rcomplex>(x);

    cpp11::r_complex x2(value);

    expect_true(x2 == x);
  }

  test_that("explicit construction from Rcomplex") {
    Rcomplex x{1, 2};
    cpp11::r_complex y(x);
    expect_true(y.real() == x.r);
    expect_true(y.imag() == x.i);
  }

  test_that("explicit construction from std::complex<double>") {
    std::complex<double> x{1, 2};
    cpp11::r_complex y(x);
    expect_true(y.real() == x.real());
    expect_true(y.imag() == x.imag());
  }

  test_that("explicit conversion to Rcomplex") {
    cpp11::r_complex x(1, 2);
    Rcomplex y(x);
    expect_true(y.r == x.real());
    expect_true(y.i == x.imag());
  }

  test_that("explicit conversion to std::complex<double>") {
    cpp11::r_complex x(1, 2);
    std::complex<double> y(x);
    expect_true(y.real() == x.real());
    expect_true(y.imag() == x.imag());
  }

  test_that("equality comparison of two r_complex") {
    expect_true(cpp11::r_complex(1, 3) == cpp11::r_complex(1, 3));
    expect_false(cpp11::r_complex(1, 3) == cpp11::r_complex(2, 3));
    expect_false(cpp11::r_complex(1, 3) == cpp11::r_complex(1, 4));
  }

  test_that("na<r_complex>()") {
    cpp11::r_complex x = cpp11::na<cpp11::r_complex>();
    // Not `ISNA()`, checking specifically for `NA_REAL`
    expect_true(R_IsNA(x.real()));
    expect_true(R_IsNA(x.imag()));
  }

  test_that("is_na(r_complex)") {
    cpp11::r_complex x{1, 2};
    expect_false(cpp11::is_na(x));

    cpp11::r_complex na_na{NA_REAL, NA_REAL};
    cpp11::r_complex na_real{NA_REAL, 1};
    cpp11::r_complex real_na{1, NA_REAL};

    expect_true(cpp11::is_na(na_na));
    expect_true(cpp11::is_na(na_real));
    expect_true(cpp11::is_na(real_na));
  }

  test_that("as_sexp(r_complex)") {
    cpp11::r_complex x{1, 2};
    cpp11::sexp value = cpp11::as_sexp(x);

    expect_true(Rf_xlength(value) == 1);
    expect_true(COMPLEX(value)[0].r == x.real());
    expect_true(COMPLEX(value)[0].i == x.imag());
  }
}
