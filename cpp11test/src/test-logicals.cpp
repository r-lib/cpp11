#include <testthat.h>
#include "cpp11/logicals.hpp"

context("logicals-C++") {
  test_that("logicals.push_back()") {
    cpp11::writable::logicals x;
    x.push_back(TRUE);
    x.push_back(FALSE);

    expect_true(x.size() == 2);
    expect_true(x[0] == TRUE);
    expect_true(x[1] == FALSE);
  }
  test_that("logicals.resize()") {
    cpp11::writable::logicals x;
    x.resize(2);
    x[0] = TRUE;
    x[1] = FALSE;

    expect_true(x.size() == 2);
    expect_true(x[0] == TRUE);
    expect_true(x[1] == FALSE);
  }
  test_that("logicals.at()") {
    cpp11::writable::logicals x;

    expect_error(x.at(-1));

    expect_error(x.at(0));

    x.push_back(TRUE);
    expect_true(x.at(0) == TRUE);
    expect_error(x.at(1));
  }
  test_that("logicals.pop_back()") {
    cpp11::writable::logicals x;

    x.push_back(TRUE);
    x.push_back(FALSE);
    x.pop_back();

    expect_true(x.size() == 1);
    expect_true(x[0] == TRUE);

    expect_error(x.at(1));
  }
  test_that("logicals.insert()") {
    cpp11::writable::logicals x;

    x.insert(0, TRUE);
    x.insert(0, FALSE);
    x.insert(1, TRUE);
    expect_true(x.size() == 3);

    expect_true(x[0] == FALSE);
    expect_true(x[1] == TRUE);
    expect_true(x[2] == TRUE);
  }
  test_that("logicals.erase()") {
    cpp11::writable::logicals x;

    x.push_back(TRUE);
    x.push_back(FALSE);
    x.push_back(NA_LOGICAL);
    x.push_back(FALSE);
    x.push_back(TRUE);

    expect_true(x.size() == 5);

    x.erase(0);

    expect_true(x.size() == 4);
    expect_true(x[0] == FALSE);
    expect_true(x[1] == NA_LOGICAL);
    expect_true(x[2] == FALSE);
    expect_true(x[3] == TRUE);

    x.erase(2);

    expect_true(x.size() == 3);
    expect_true(x[0] == FALSE);
    expect_true(x[1] == NA_LOGICAL);
    expect_true(x[2] == TRUE);
  }
  test_that("logicals.iterator* = ") {
    cpp11::writable::logicals x;
    x.push_back(TRUE);
    x.push_back(FALSE);
    x.push_back(FALSE);
    auto it = x.begin() + 1;
    *it = TRUE;
    ++it;
    *it = FALSE;

    expect_true(x.size() == 3);
    expect_true(x[0] == TRUE);
    expect_true(x[1] == TRUE);
    expect_true(x[2] == FALSE);
  }

  test_that("writable::logicals(SEXP)") {
    SEXP x = PROTECT(Rf_allocVector(LGLSXP, 5));

    LOGICAL(x)[0] = TRUE;
    LOGICAL(x)[1] = TRUE;
    LOGICAL(x)[2] = TRUE;
    LOGICAL(x)[3] = TRUE;
    LOGICAL(x)[4] = TRUE;

    cpp11::writable::logicals y(x);
    y[0] = FALSE;

    expect_true(x != y.data());

    expect_true(LOGICAL(x)[0] == 1);
    expect_true(y[0] == FALSE);

    cpp11::writable::logicals z(y);
    z[0] = TRUE;

    expect_true(z.data() != y.data());

    expect_true(LOGICAL(x)[0] == 1);
    expect_true(y[0] == FALSE);
    expect_true(z[0] == TRUE);

    UNPROTECT(1);
  }
  test_that("writable::logicals::proxy::operator=(bool)") {
    cpp11::writable::logicals y(2);

    y[0] = false;
    y[1] = true;
    expect_true(y[0] == TRUE);
    expect_true(y[1] == FALSE);
  }
  test_that("is_na(Rboolean)") {
    Rboolean x = TRUE;
    expect_true(!cpp11::is_na(x));

    Rboolean y = NA_LOGICAL;
    expect_true(cpp11::is_na(y));
  }

  // test_that("writable::logicals(ALTREP_SEXP)") {
  // SEXP x = PROTECT(R_compact_intrange(1, 5));
  //// Need to find (or create) an altrep class that implements duplicate.

  // cpp11::writable::logicals y(x);
  // y[0] = -1;

  // expect_true(x != y.data());

  // expect_true(logical_ELT(x, 0) == 1);
  // expect_true(y[0] == -1);

  // cpp11::writable::logicals z(y);
  // z[0] = -2;

  // expect_true(z.data() != y.data());

  // expect_true(logical_ELT(x, 0) == 1);
  // expect_true(y[0] == -1);
  // expect_true(z[0] == -2);

  // z.push_back(6);
  // expect_true(z[5] == 6);

  // UNPROTECT(1);
  //}
}
