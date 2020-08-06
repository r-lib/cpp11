#include <testthat.h>

#include <deque>
#include <string>
#include <vector>

#include "cpp11/declarations.hpp"

#include "Rcpp.h"

context("as_cpp-C++") {
  test_that("as_cpp<integer>(INTSEXP)") {
    SEXP r = PROTECT(Rf_allocVector(INTSXP, 1));
    INTEGER(r)[0] = 42;
    auto x1 = cpp11::as_cpp<int>(r);
    expect_true(x1 == 42);

    auto x2 = cpp11::as_cpp<long>(r);
    expect_true(x2 == 42L);

    auto x3 = cpp11::as_cpp<long long int>(r);
    expect_true(x3 == 42LL);

    auto x4 = cpp11::as_cpp<unsigned>(r);
    expect_true(x4 == 42U);

    auto x5 = cpp11::as_cpp<unsigned long>(r);
    expect_true(x5 == 42UL);

    UNPROTECT(1);
  }

  test_that("as_cpp<integer>(REALSEXP)") {
    SEXP r = PROTECT(Rf_allocVector(REALSXP, 1));
    REAL(r)[0] = 42;
    auto x1 = cpp11::as_cpp<int>(r);
    expect_true(x1 == 42);

    auto x2 = cpp11::as_cpp<long>(r);
    expect_true(x2 == 42L);

    auto x3 = cpp11::as_cpp<long long int>(r);
    expect_true(x3 == 42LL);

    auto x4 = cpp11::as_cpp<unsigned>(r);
    expect_true(x4 == 42U);

    auto x5 = cpp11::as_cpp<unsigned long>(r);
    expect_true(x5 == 42UL);

#ifdef HAS_UNWIND_PROTECT
    /* throws a runtime exception if the value is not a integerish one */
    REAL(r)[0] = 42.5;
    expect_error(cpp11::as_cpp<int>(r));
#endif

    UNPROTECT(1);
  }

  test_that("as_cpp<integer>(NA)") {
    SEXP r = PROTECT(Rf_allocVector(REALSXP, 1));
    SEXP i = PROTECT(Rf_allocVector(INTSXP, 1));
    SEXP l = PROTECT(Rf_allocVector(LGLSXP, 1));
    REAL(r)[0] = NA_REAL;
    INTEGER(i)[0] = NA_INTEGER;
    LOGICAL(l)[0] = NA_LOGICAL;

    auto x1 = cpp11::as_cpp<int>(r);
    expect_true(x1 == NA_INTEGER);

    auto x2 = cpp11::as_cpp<int>(i);
    expect_true(x2 == NA_INTEGER);

    auto x3 = cpp11::as_cpp<int>(l);
    expect_true(x3 == NA_INTEGER);

    UNPROTECT(3);
  }

  test_that("as_cpp<enum>(INTSEXP)") {
    enum Response { YES, NO, MAYBE };
    SEXP r = PROTECT(Rf_allocVector(INTSXP, 1));

    for (Response e : {YES, NO, MAYBE, static_cast<Response>(42)}) {
      INTEGER(r)[0] = static_cast<int>(e);
      auto x = cpp11::as_cpp<Response>(r);
      expect_true(x == e);
    }

    UNPROTECT(1);
  }

  test_that("as_cpp<double>(REALSXP)") {
    SEXP r = PROTECT(Rf_allocVector(REALSXP, 1));
    REAL(r)[0] = 1.2;
    auto x1 = cpp11::as_cpp<float>(r);
    expect_true(x1 == 1.2f);

    auto x2 = cpp11::as_cpp<double>(r);
    expect_true(x2 == 1.2);

    auto x3 = cpp11::as_cpp<long double>(r);
    expect_true(x3 == 1.2);

    UNPROTECT(1);
  }

  test_that("as_cpp<double>(INTSXP)") {
    SEXP r = PROTECT(Rf_allocVector(INTSXP, 1));
    INTEGER(r)[0] = 1;
    auto x1 = cpp11::as_cpp<float>(r);
    expect_true(x1 == 1.f);

    auto x2 = cpp11::as_cpp<double>(r);
    expect_true(x2 == 1.);

    auto x3 = cpp11::as_cpp<long double>(r);
    expect_true(x3 == 1.);

    UNPROTECT(1);
  }

  test_that("as_cpp<double>(NA)") {
    SEXP r = PROTECT(Rf_allocVector(REALSXP, 1));
    SEXP i = PROTECT(Rf_allocVector(INTSXP, 1));
    SEXP l = PROTECT(Rf_allocVector(LGLSXP, 1));
    REAL(r)[0] = NA_REAL;
    INTEGER(i)[0] = NA_INTEGER;
    LOGICAL(l)[0] = NA_LOGICAL;

    auto x1 = cpp11::as_cpp<double>(r);
    expect_true(ISNA(x1));

    auto x2 = cpp11::as_cpp<double>(i);
    expect_true(ISNA(x2));

    auto x3 = cpp11::as_cpp<double>(l);
    expect_true(ISNA(x3));

    UNPROTECT(3);
  }

  test_that("as_cpp<bool>()") {
    SEXP r = PROTECT(Rf_allocVector(LGLSXP, 1));
    LOGICAL(r)[0] = TRUE;
    auto x1 = cpp11::as_cpp<bool>(r);
    expect_true(x1);

    LOGICAL(r)[0] = FALSE;
    auto x2 = cpp11::as_cpp<bool>(r);
    expect_true(!x2);

    UNPROTECT(1);
  }

  test_that("as_cpp<char>()") {
    SEXP r = PROTECT(Rf_allocVector(STRSXP, 1));
    SET_STRING_ELT(r, 0, Rf_mkChar("foo"));

    auto x1 = cpp11::as_cpp<char>(r);
    expect_true(x1 == 'f');

    UNPROTECT(1);
  }

  test_that("as_cpp<const char*>()") {
    SEXP r = PROTECT(Rf_allocVector(STRSXP, 1));
    SET_STRING_ELT(r, 0, Rf_mkChar("foo"));
    auto x1 = cpp11::as_cpp<const char*>(r);

    expect_true(strcmp(x1, "foo") == 0);
    UNPROTECT(1);
  }

  test_that("as_cpp<std::string>()") {
    SEXP r = PROTECT(Rf_allocVector(STRSXP, 1));
    SET_STRING_ELT(r, 0, Rf_mkChar("foo"));
    auto x1 = cpp11::as_cpp<std::string>(r);
    expect_true(x1 == "foo");

    UNPROTECT(1);
  }

  test_that("as_cpp<std::vector<int>>()") {
    SEXP r = PROTECT(Rf_allocVector(INTSXP, 3));
    INTEGER(r)[0] = 1;
    INTEGER(r)[1] = 2;
    INTEGER(r)[2] = 3;

    auto x1 = cpp11::as_cpp<std::vector<int>>(r);
    expect_true(x1[0] == 1);
    expect_true(x1[1] == 2);
    expect_true(x1[2] == 3);

    UNPROTECT(1);
  }

  test_that("as_cpp<std::vector<std::string>>()") {
    SEXP r = PROTECT(Rf_allocVector(STRSXP, 3));
    SET_STRING_ELT(r, 0, Rf_mkChar("foo"));
    SET_STRING_ELT(r, 1, Rf_mkChar("bar"));
    SET_STRING_ELT(r, 2, Rf_mkChar("baz"));

    auto x1 = cpp11::as_cpp<std::vector<std::string>>(r);
    expect_true(x1[0] == "foo");
    expect_true(x1[1] == "bar");
    expect_true(x1[2] == "baz");

    UNPROTECT(1);
  }

  test_that("as_cpp<std::deque<string>>()") {
    SEXP r = PROTECT(Rf_allocVector(STRSXP, 3));
    SET_STRING_ELT(r, 0, Rf_mkChar("foo"));
    SET_STRING_ELT(r, 1, Rf_mkChar("bar"));
    SET_STRING_ELT(r, 2, Rf_mkChar("baz"));

    auto x1 = cpp11::as_cpp<std::deque<std::string>>(r);
    expect_true(x1[0] == "foo");
    expect_true(x1[1] == "bar");
    expect_true(x1[2] == "baz");

    UNPROTECT(1);
  }

  test_that("as_cpp<doubles>()") {
    SEXP r = PROTECT(Rf_allocVector(REALSXP, 3));
    REAL(r)[0] = 1.;
    REAL(r)[1] = 2.;
    REAL(r)[2] = 3.;

    auto x1 = cpp11::as_cpp<cpp11::doubles>(r);
    expect_true(x1[0] == 1.);
    expect_true(x1[1] == 2.);
    expect_true(x1[2] == 3.);

    UNPROTECT(1);
  }

  test_that("as_cpp<Rcpp::List>()") {
    SEXP l1 = PROTECT(Rf_allocVector(VECSXP, 3));
    SET_VECTOR_ELT(l1, 0, Rf_allocVector(VECSXP, 1));
    SET_VECTOR_ELT(VECTOR_ELT(l1, 0), 0, Rf_mkString("foo"));

    auto res1 = cpp11::as_cpp<Rcpp::List>(l1);
    auto res2 = Rcpp::List(l1);

    expect_true(Rf_length(res1) == Rf_length(res2));

    SEXP res3 = cpp11::as_sexp(res2);

    expect_true(Rf_length(res3) == Rf_length(res2));

    UNPROTECT(1);
  }

  test_that("as_sexp(integer)") {
    SEXP i1 = PROTECT(cpp11::as_sexp(42));
    SEXP i2 = PROTECT(cpp11::as_sexp(42L));
    SEXP i3 = PROTECT(cpp11::as_sexp(42LL));
    SEXP i4 = PROTECT(cpp11::as_sexp(42U));
    SEXP i5 = PROTECT(cpp11::as_sexp(42UL));
    SEXP i6 = PROTECT(cpp11::as_sexp(NA_INTEGER));

    expect_true(Rf_isInteger(i1));
    expect_true(Rf_xlength(i1) == 1);
    expect_true(INTEGER(i1)[0] == 42);

    expect_true(Rf_isInteger(i2));
    expect_true(Rf_xlength(i2) == 1);
    expect_true(INTEGER(i2)[0] == 42);

    expect_true(Rf_isInteger(i3));
    expect_true(Rf_xlength(i3) == 1);
    expect_true(INTEGER(i3)[0] == 42);

    expect_true(Rf_isInteger(i4));
    expect_true(Rf_xlength(i4) == 1);
    expect_true(INTEGER(i4)[0] == 42);

    expect_true(Rf_isInteger(i5));
    expect_true(Rf_xlength(i5) == 1);
    expect_true(INTEGER(i5)[0] == 42);

    expect_true(Rf_isInteger(i6));
    expect_true(Rf_xlength(i6) == 1);
    expect_true(INTEGER(i6)[0] == NA_INTEGER);

    UNPROTECT(6);
  }

  test_that("as_sexp(floating_point)") {
    SEXP f1 = PROTECT(cpp11::as_sexp(1.2f));
    SEXP f2 = PROTECT(cpp11::as_sexp(1.2));
    SEXP f3 = PROTECT(cpp11::as_sexp(1.2l));
    SEXP f4 = PROTECT(cpp11::as_sexp(NA_REAL));

    expect_true(Rf_isReal(f1));
    expect_true(Rf_xlength(f1) == 1);
    expect_true(REAL(f1)[0] == 1.2f);

    expect_true(Rf_isReal(f2));
    expect_true(Rf_xlength(f2) == 1);
    expect_true(REAL(f2)[0] == 1.2);

    expect_true(Rf_isReal(f3));
    expect_true(Rf_xlength(f3) == 1);
    expect_true(REAL(f3)[0] == 1.2);

    expect_true(Rf_isReal(f4));
    expect_true(Rf_xlength(f4) == 1);
    expect_true(ISNA(REAL(f4)[0]));

    UNPROTECT(4);
  }

  test_that("as_sexp(bool)") {
    SEXP l1 = PROTECT(cpp11::as_sexp(true));
    SEXP l2 = PROTECT(cpp11::as_sexp(false));
    /* TODO: handle NA_LOGICAL, possibly need a separate enum class rather than relying
     * on bool or R's Rboolean */

    expect_true(Rf_isLogical(l1));
    expect_true(Rf_xlength(l1) == 1);
    expect_true(LOGICAL(l1)[0] == TRUE);

    expect_true(Rf_isLogical(l2));
    expect_true(Rf_xlength(l2) == 1);
    expect_true(LOGICAL(l2)[0] == FALSE);

    UNPROTECT(2);
  }

  test_that("as_sexp(raws)") {
    cpp11::writable::raws x;
    x.push_back(0);
    x.push_back(1);
    x.push_back(2);

    auto res1 = cpp11::as_sexp(x);
    expect_true(TYPEOF(res1) == RAWSXP);
    expect_true(RAW(res1)[0] == 0);
    expect_true(RAW(res1)[1] == 1);
    expect_true(RAW(res1)[2] == 2);

    cpp11::raws y(x);

    auto res2 = cpp11::as_sexp(y);
    expect_true(TYPEOF(res2) == RAWSXP);
    expect_true(RAW(res2)[0] == 0);
    expect_true(RAW(res2)[1] == 1);
    expect_true(RAW(res2)[2] == 2);
  }

  test_that("as_sexp(stringish)") {
    SEXP s1 = PROTECT(cpp11::as_sexp("foo"));
    SEXP s2 = PROTECT(cpp11::as_sexp(std::string("foo")));
    SEXP s3 = PROTECT(cpp11::as_sexp(cpp11::r_string("foo")));

    expect_true(Rf_isString(s1));
    expect_true(Rf_xlength(s1) == 1);
    expect_true(strcmp(CHAR(STRING_ELT(s1, 0)), "foo") == 0);

    expect_true(Rf_isString(s2));
    expect_true(Rf_xlength(s2) == 1);
    expect_true(strcmp(CHAR(STRING_ELT(s2, 0)), "foo") == 0);

    expect_true(Rf_isString(s3));
    expect_true(Rf_xlength(s3) == 1);
    expect_true(strcmp(CHAR(STRING_ELT(s3, 0)), "foo") == 0);

    UNPROTECT(3);
  }

  test_that("as_sexp(r_vector<int>)") {
    SEXP i1 = PROTECT(cpp11::as_sexp(std::vector<int>({1, 2, 3})));

    expect_true(Rf_isInteger(i1));
    expect_true(Rf_xlength(i1) == 3);
    expect_true(INTEGER(i1)[0] == 1);
    expect_true(INTEGER(i1)[1] == 2);
    expect_true(INTEGER(i1)[2] == 3);

    UNPROTECT(1);
  }

  test_that("as_sexp(r_vector<floating_point>)") {
    SEXP r1 = PROTECT(cpp11::as_sexp(std::vector<double>({0.1, 0.2, 0.3})));

    expect_true(Rf_isReal(r1));
    expect_true(Rf_xlength(r1) == 3);
    expect_true(REAL(r1)[0] == 0.1);
    expect_true(REAL(r1)[1] == 0.2);
    expect_true(REAL(r1)[2] == 0.3);

    UNPROTECT(1);
  }

  test_that("as_sexp(r_vector<floating_point>)") {
    SEXP l1 = PROTECT(cpp11::as_sexp(std::vector<bool>({true, false, true})));

    expect_true(Rf_isLogical(l1));
    expect_true(Rf_xlength(l1) == 3);
    expect_true(LOGICAL(l1)[0] == true);
    expect_true(LOGICAL(l1)[1] == false);
    expect_true(LOGICAL(l1)[2] == true);

    UNPROTECT(1);
  }

  test_that("as_sexp(r_vector<std::string>)") {
    SEXP s1 = PROTECT(cpp11::as_sexp(std::vector<std::string>({"foo", "bar", "baz"})));

    expect_true(Rf_isString(s1));
    expect_true(Rf_xlength(s1) == 3);
    expect_true(strcmp(CHAR(STRING_ELT(s1, 0)), "foo") == 0);
    expect_true(strcmp(CHAR(STRING_ELT(s1, 1)), "bar") == 0);
    expect_true(strcmp(CHAR(STRING_ELT(s1, 2)), "baz") == 0);

    UNPROTECT(1);
  }

  test_that("as_sexp(cpp11::strings)") {
    cpp11::writable::strings s({"foo", "bar", "baz"});
    cpp11::strings s0(s);
    SEXP s1 = PROTECT(cpp11::as_sexp(s0));

    expect_true(Rf_isString(s1));
    expect_true(Rf_xlength(s1) == 3);
    expect_true(strcmp(CHAR(STRING_ELT(s1, 0)), "foo") == 0);
    expect_true(strcmp(CHAR(STRING_ELT(s1, 1)), "bar") == 0);
    expect_true(strcmp(CHAR(STRING_ELT(s1, 2)), "baz") == 0);

    UNPROTECT(1);
  }

  test_that("as_sexp(initializer_list<const char*>)") {
    SEXP s1 = PROTECT(cpp11::as_sexp({"foo", "bar", "baz"}));

    expect_true(Rf_isString(s1));
    expect_true(Rf_xlength(s1) == 3);
    expect_true(strcmp(CHAR(STRING_ELT(s1, 0)), "foo") == 0);
    expect_true(strcmp(CHAR(STRING_ELT(s1, 1)), "bar") == 0);
    expect_true(strcmp(CHAR(STRING_ELT(s1, 2)), "baz") == 0);

    UNPROTECT(1);
  }
}
