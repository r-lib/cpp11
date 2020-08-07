#include "cpp11/protect.hpp"
#include "testthat.h"

#ifdef HAS_UNWIND_PROTECT
context("unwind_protect-C++") {
  test_that("unwind_protect works if there is no error") {
    SEXP out = PROTECT(cpp11::unwind_protect([&] {
      out = PROTECT(Rf_allocVector(REALSXP, 1));
      REAL(out)[0] = 1;
      UNPROTECT(1);
      return out;
    }));

    expect_true(Rf_xlength(out) == 1);
    expect_true(REAL(out)[0] == 1);

    UNPROTECT(1);
  }
  test_that("unwind_protect throws a C++ exception if there is an R error") {
    SEXP out;
    expect_error_as(cpp11::unwind_protect([&] {
                      out = PROTECT(Rf_allocVector(REALSXP, -1));
                      REAL(out)[0] = 1;
                      UNPROTECT(1);
                      return out;
                    }),
                    cpp11::unwind_exception);
  }

  test_that("safe wraps R functions and works if there is no error") {
    SEXP out = PROTECT(cpp11::safe[Rf_allocVector](REALSXP, 1));
    REAL(out)[0] = 1;

    expect_true(Rf_xlength(out) == 1);
    expect_true(REAL(out)[0] == 1);

    UNPROTECT(1);
  }

  test_that("stop throws an unwind_exception") {
    expect_error_as(cpp11::stop("error"), cpp11::unwind_exception);
    expect_error_as(cpp11::stop("error: %s", "message"), cpp11::unwind_exception);
  }

  test_that("safe wraps R functions and works if there is an R error") {
    expect_error_as(cpp11::safe[Rf_allocVector](REALSXP, -1), cpp11::unwind_exception);
  }
}

#endif
