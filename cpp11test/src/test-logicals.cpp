#include "cpp11/logicals.hpp"

#include <testthat.h>

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

  test_that("writable::logicals(initializer_list<named_arg>)") {
    using namespace cpp11::literals;

    SEXP x1 = PROTECT(Rf_allocVector(LGLSXP, 1));
    SEXP x2 = PROTECT(Rf_allocVector(LGLSXP, 1));
    SEXP x3 = PROTECT(Rf_allocVector(LGLSXP, 1));

    SET_LOGICAL_ELT(x1, 0, 0);
    SET_LOGICAL_ELT(x2, 0, 1);
    SET_LOGICAL_ELT(x3, 0, NA_LOGICAL);

    // From scalar logical vectors
    cpp11::writable::logicals x({"one"_nm = x1, "two"_nm = x2, "three"_nm = x3});
    expect_true(x.named());
    expect_true(x["one"] == cpp11::r_bool(false));
    expect_true(x["two"] == cpp11::r_bool(true));
    expect_true(x["three"] == cpp11::r_bool(NA_LOGICAL));

    // From booleans
    cpp11::writable::logicals y({"one"_nm = true, "two"_nm = false, "three"_nm = true});
    expect_true(y.named());
    expect_true(y["one"] == cpp11::r_bool(true));
    expect_true(y["two"] == cpp11::r_bool(false));
    expect_true(y["three"] == cpp11::r_bool(true));

    UNPROTECT(3);
  }

  test_that("writable::logicals(initializer_list<named_arg>) type check") {
    using namespace cpp11::literals;
    expect_error_as(cpp11::writable::logicals({"one"_nm = 1}), cpp11::type_error);
    expect_error_as(cpp11::writable::logicals({"one"_nm = R_NilValue}),
                    cpp11::type_error);
  }

  test_that("writable::logicals(initializer_list<named_arg>) length check") {
    using namespace cpp11::literals;
    SEXP x = PROTECT(Rf_allocVector(LGLSXP, 2));
    expect_error_as(cpp11::writable::logicals({"x"_nm = x}), std::length_error);
    UNPROTECT(1);
  }

  test_that("writable::logicals(initializer_list<r_bool>)") {
    cpp11::writable::logicals x(
        {cpp11::r_bool(true), cpp11::r_bool(false), cpp11::r_bool(NA_INTEGER)});
    expect_true(x[0] == cpp11::r_bool(true));
    expect_true(x[1] == cpp11::r_bool(false));
    expect_true(x[2] == cpp11::r_bool(NA_INTEGER));

    // This works due to implicit conversion of `bool` to `r_bool`
    cpp11::writable::logicals y({true, false, false});
    expect_true(y[0] == cpp11::r_bool(true));
    expect_true(y[1] == cpp11::r_bool(false));
    expect_true(y[2] == cpp11::r_bool(false));

    // This works due to implicit conversion of `Rboolean` to `r_bool`
    cpp11::writable::logicals z({TRUE, FALSE, FALSE});
    expect_true(z[0] == cpp11::r_bool(true));
    expect_true(z[1] == cpp11::r_bool(false));
    expect_true(z[2] == cpp11::r_bool(false));
  }

  test_that("is_na(r_bool)") {
    cpp11::r_bool x = TRUE;
    expect_true(!cpp11::is_na(x));

    cpp11::r_bool y = NA_LOGICAL;
    expect_true(cpp11::is_na(y));
  }

  test_that("FALSE and false") {
    cpp11::writable::logicals x{FALSE};
    expect_true(x.size() == 1);
    expect_true(x[0] == FALSE);

    cpp11::writable::logicals y{false};
    expect_true(y.size() == 1);
    expect_true(y[0] == FALSE);
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
