#include <testthat.h>
#include "cpp11/strings.hpp"

context("strings-C++") {
  test_that("strings.push_back()") {
    cpp11::writable::strings x;
    x.push_back("a");
    x.push_back("b");

    expect_true(x.size() == 2);
    expect_true(x[0] == "a");
    expect_true(x[1] == "b");
  }
  test_that("strings.resize()") {
    cpp11::writable::strings x;
    x.resize(2);
    x[0] = "a";
    x[1] = "b";

    expect_true(x.size() == 2);
    expect_true(x[0] == "a");
    expect_true(x[1] == "b");
  }
  test_that("strings.at()") {
    cpp11::writable::strings x;

    expect_error(x.at(-1));

    expect_error(x.at(0));

    x.push_back("a");
    auto test = x.at(0);
    expect_true(test == "a");
    expect_error(x.at(1));
  }
  test_that("strings.pop_back()") {
    cpp11::writable::strings x;

    x.push_back("a");
    x.push_back("b");
    x.pop_back();

    expect_true(x.size() == 1);
    expect_true(x[0] == "a");

    expect_error(x.at(1));
  }
  test_that("strings.insert()") {
    cpp11::writable::strings x;

    x.insert(0, "a");
    x.insert(0, "b");
    x.insert(1, "c");
    expect_true(x.size() == 3);

    expect_true(x[0] == "b");
    expect_true(x[1] == "c");
    expect_true(x[2] == "a");
  }

  test_that("strings.erase()") {
    cpp11::writable::strings x;

    x.push_back("a");
    x.push_back("b");
    x.push_back("c");
    x.push_back("d");
    x.push_back("e");

    expect_true(x.size() == 5);

    x.erase(0);

    expect_true(x.size() == 4);
    expect_true(x[0] == "b");
    expect_true(x[1] == "c");
    expect_true(x[2] == "d");
    expect_true(x[3] == "e");

    x.erase(2);

    expect_true(x.size() == 3);
    expect_true(x[0] == "b");
    expect_true(x[1] == "c");
    expect_true(x[2] == "e");
  }

  test_that("strings.iterator* = ") {
    cpp11::writable::strings x;
    x.push_back("a");
    x.push_back("b");
    x.push_back("c");
    auto it = x.begin() + 1;
    *it = "d";
    ++it;
    *it = "e";

    expect_true(x.size() == 3);
    expect_true(x[0] == "a");
    expect_true(x[1] == "d");
    expect_true(x[2] == "e");
  }

  test_that("writable::strings(SEXP)") {
    SEXP x = PROTECT(Rf_allocVector(STRSXP, 5));

    SET_STRING_ELT(x, 0, Rf_mkCharCE("a", CE_UTF8));
    SET_STRING_ELT(x, 1, Rf_mkCharCE("b", CE_UTF8));
    SET_STRING_ELT(x, 2, Rf_mkCharCE("c", CE_UTF8));
    SET_STRING_ELT(x, 3, Rf_mkCharCE("d", CE_UTF8));
    SET_STRING_ELT(x, 4, Rf_mkCharCE("e", CE_UTF8));

    cpp11::writable::strings y(x);
    y[0] = "foo";

    expect_true(x != y.data());

    expect_true(std::string(CHAR(STRING_ELT(x, 0))) == "a");
    expect_true(y[0] == "foo");

    cpp11::writable::strings z(y);
    z[0] = "bar";

    expect_true(z.data() != y.data());

    expect_true(std::string(CHAR(STRING_ELT(x, 0))) == "a");
    expect_true(y[0] == "foo");
    expect_true(z[0] == "bar");

    UNPROTECT(1);
  }

  test_that("NA_STRING constructor") {
    cpp11::writable::strings x({NA_STRING});

    expect_true(x.size() == 1);
    expect_true(x[0] == NA_STRING);

    cpp11::writable::strings y({NA_STRING, "foo"});

    expect_true(y.size() == 2);
    expect_true(y[0] == NA_STRING);
    expect_true(y[1] == "foo");
  }

  // test_that("writable::strings(ALTREP_SEXP)") {
  // SEXP x = PROTECT(R_compact_uint8_trange(1, 5));
  //// Need to find (or create) an altrep class that implements duplicate.

  // cpp11::writable::strings y(x);
  // y[0] = -1;

  // expect_true(x != y.data());

  // expect_true(raw_ELT(x, 0) == 1);
  // expect_true(y[0] == -1);

  // cpp11::writable::strings z(y);
  // z[0] = -2;

  // expect_true(z.data() != y.data());

  // expect_true(raw_ELT(x, 0) == 1);
  // expect_true(y[0] == -1);
  // expect_true(z[0] == -2);

  // z.push_back(6);
  // expect_true(z[5] == 6);

  // UNPROTECT(1);
  //}
}
