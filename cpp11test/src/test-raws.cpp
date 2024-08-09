#include "cpp11/raws.hpp"

#include <testthat.h>

context("raws-C++") {
  test_that("raws.push_back()") {
    cpp11::writable::raws x;
    x.push_back('a');
    x.push_back('b');

    expect_true(x.size() == 2);
    expect_true(x[0] == 'a');
    expect_true(x[1] == 'b');
  }
  test_that("raws.resize()") {
    cpp11::writable::raws x;
    x.resize(2);
    x[0] = 'a';
    x[1] = 'b';

    expect_true(x.size() == 2);
    expect_true(x[0] == 'a');
    expect_true(x[1] == 'b');
  }
  test_that("raws.at()") {
    cpp11::writable::raws x;

    expect_error(x.at(-1));

    expect_error(x.at(0));

    x.push_back('a');
    expect_true(x.at(0) == 'a');
    expect_error(x.at(1));
  }
  test_that("raws.pop_back()") {
    cpp11::writable::raws x;

    x.push_back('a');
    x.push_back('b');
    x.pop_back();

    expect_true(x.size() == 1);
    expect_true(x[0] == 'a');

    expect_error(x.at(1));
  }
  test_that("raws.insert()") {
    cpp11::writable::raws x;

    x.insert(0, 'a');
    x.insert(0, 'b');
    x.insert(1, 'c');
    expect_true(x.size() == 3);

    expect_true(x[0] == 'b');
    expect_true(x[1] == 'c');
    expect_true(x[2] == 'a');
  }
  test_that("raws.erase()") {
    cpp11::writable::raws x;

    x.push_back('a');
    x.push_back('b');
    x.push_back('c');
    x.push_back('d');
    x.push_back('e');

    expect_true(x.size() == 5);

    x.erase(0);

    expect_true(x.size() == 4);
    expect_true(x[0] == 'b');
    expect_true(x[1] == 'c');
    expect_true(x[2] == 'd');
    expect_true(x[3] == 'e');

    x.erase(2);

    expect_true(x.size() == 3);
    expect_true(x[0] == 'b');
    expect_true(x[1] == 'c');
    expect_true(x[2] == 'e');
  }
  test_that("raws.iterator* = ") {
    cpp11::writable::raws x;
    x.push_back('a');
    x.push_back('b');
    x.push_back('c');
    auto it = x.begin() + 1;
    *it = 'd';
    ++it;
    *it = 'e';

    expect_true(x.size() == 3);
    expect_true(x[0] == 'a');
    expect_true(x[1] == 'd');
    expect_true(x[2] == 'e');
  }

  test_that("writable::raws(SEXP)") {
    SEXP x = PROTECT(Rf_allocVector(RAWSXP, 5));

    RAW(x)[0] = 'a';
    RAW(x)[1] = 'b';
    RAW(x)[2] = 'c';
    RAW(x)[3] = 'd';
    RAW(x)[4] = 'e';

    cpp11::writable::raws y(x);
    y[0] = '\0';

    expect_true(x != y.data());

    expect_true(RAW(x)[0] == 'a');
    expect_true(y[0] == '\0');

    cpp11::writable::raws z(y);
    z[0] = 'f';

    expect_true(z.data() != y.data());

    expect_true(RAW(x)[0] == 'a');
    expect_true(y[0] == '\0');
    expect_true(z[0] == 'f');

    UNPROTECT(1);
  }

  test_that("writable::raws(initializer_list<uint_8>)") {
    cpp11::writable::raws x({1, 2, 255});
    expect_true(x[0] == 1);
    expect_true(x[1] == 2);
    expect_true(x[2] == 255);
  }

  // test_that("writable::raws(ALTREP_SEXP)") {
  // SEXP x = PROTECT(R_compact_uint8_trange(1, 5));
  //// Need to find (or create) an altrep class that implements duplicate.

  // cpp11::writable::raws y(x);
  // y[0] = -1;

  // expect_true(x != y.data());

  // expect_true(raw_ELT(x, 0) == 1);
  // expect_true(y[0] == -1);

  // cpp11::writable::raws z(y);
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
