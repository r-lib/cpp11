#include "Rversion.h"
#include "cpp11/doubles.hpp"
#include "cpp11/function.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/strings.hpp"

#include <testthat.h>

context("integers-C++") {
  test_that("as_integers(doubles)") {
    // TYPEOF(x) == INTSXP
    cpp11::writable::doubles y;
    y.push_back(10.00);
    cpp11::writable::integers i(cpp11::as_integers(y));
    expect_true(i[0] == 10);
    expect_true(TYPEOF(i) == INTSXP);

    cpp11::writable::doubles x;
    x.push_back(10.01);
    expect_error(cpp11::as_integers(x));

    cpp11::writable::strings e;
    e.push_back("a");
    e.push_back("b");
    expect_error(cpp11::as_integers(e));

    cpp11::writable::doubles z;
    z.push_back(10);
    z.push_back(1000);
    z.push_back(100000);
    z.push_back(100000.00);

    cpp11::writable::integers t((cpp11::as_integers(z)));
    expect_true(t[0] == 10);
    expect_true(t[1] == 1000);
    expect_true(t[2] == 100000);
    expect_true(t[3] == 100000);
    expect_true(TYPEOF(t) == INTSXP);

    cpp11::writable::doubles na{NA_REAL, 42.};
    cpp11::integers na2(cpp11::as_integers(na));
    expect_true(cpp11::is_na(na2[0]));
    expect_true(!cpp11::is_na(na2[1]));
  }

  test_that("integers.push_back()") {
    cpp11::writable::integers x;
    x.push_back(1);
    x.push_back(2);

    expect_true(x.size() == 2);
    expect_true(x[0] == 1);
    expect_true(x[1] == 2);
  }
  test_that("integers.resize()") {
    cpp11::writable::integers x;
    x.resize(2);
    x[0] = 1;
    x[1] = 2;

    expect_true(x.size() == 2);
    expect_true(x[0] == 1);
    expect_true(x[1] == 2);
  }
  test_that("integers.at()") {
    cpp11::writable::integers x;

    expect_error(x.at(-1));

    expect_error(x.at(0));

    x.push_back(1);
    expect_true(x.at(0) == 1);
    expect_error(x.at(1));
  }
  test_that("integers.pop_back()") {
    cpp11::writable::integers x;

    x.push_back(1);
    x.push_back(2);
    x.pop_back();

    expect_true(x.size() == 1);
    expect_true(x[0] == 1);

    expect_error(x.at(1));
  }
  test_that("integers.insert()") {
    cpp11::writable::integers x;

    x.insert(0, 1);
    x.insert(0, 2);
    x.insert(1, 3);
    expect_true(x.size() == 3);

    expect_true(x[0] == 2);
    expect_true(x[1] == 3);
    expect_true(x[2] == 1);
  }
  test_that("integers.erase()") {
    cpp11::writable::integers x;

    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    expect_true(x.size() == 5);

    x.erase(0);

    expect_true(x.size() == 4);
    expect_true(x[0] == 2);
    expect_true(x[1] == 3);
    expect_true(x[2] == 4);
    expect_true(x[3] == 5);

    x.erase(2);

    expect_true(x.size() == 3);
    expect_true(x[0] == 2);
    expect_true(x[1] == 3);
    expect_true(x[2] == 5);
  }
  test_that("integers.iterator* = ") {
    cpp11::writable::integers x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    auto it = x.begin() + 1;
    *it = 3;
    ++it;
    *it = 4;

    expect_true(x.size() == 3);
    expect_true(x[0] == 1);
    expect_true(x[1] == 3);
    expect_true(x[2] == 4);
  }

  test_that("writable::integers(SEXP)") {
    SEXP x = PROTECT(Rf_allocVector(INTSXP, 5));

    INTEGER(x)[0] = 1;
    INTEGER(x)[1] = 2;
    INTEGER(x)[2] = 3;
    INTEGER(x)[3] = 4;
    INTEGER(x)[4] = 5;

    cpp11::writable::integers y(x);
    y[0] = -1;

    expect_true(x != y.data());

    expect_true(INTEGER(x)[0] == 1);
    expect_true(y[0] == -1);

    cpp11::writable::integers z(y);
    z[0] = -2;

    expect_true(z.data() != y.data());

    expect_true(INTEGER(x)[0] == 1);
    expect_true(y[0] == -1);
    expect_true(z[0] == -2);

    UNPROTECT(1);
  }

#if defined(__APPLE__) && defined(R_VERSION) && R_VERSION >= R_Version(3, 5, 0)
  test_that("writable::integers(ALTREP_SEXP)") {
    // ALTREP compact-seq
    auto seq = cpp11::package("base")["seq"];
    SEXP x = PROTECT(seq(cpp11::as_sexp(1), cpp11::as_sexp(5)));
    expect_true(ALTREP(x));
    // Need to find (or create) an altrep class that implements duplicate.

    cpp11::writable::integers y(x);
    y[0] = -1;

    expect_true(x != y.data());

    expect_true(INTEGER_ELT(x, 0) == 1);
    expect_true(y[0] == -1);

    cpp11::writable::integers z(y);
    z[0] = -2;

    expect_true(z.data() != y.data());

    expect_true(INTEGER_ELT(x, 0) == 1);
    expect_true(y[0] == -1);
    expect_true(z[0] == -2);

    z.push_back(6);
    expect_true(z[5] == 6);

    UNPROTECT(1);
  }
#endif

  test_that("is_na(integer)") {
    int x = 0;
    expect_true(!cpp11::is_na(x));

    int y = NA_INTEGER;
    expect_true(cpp11::is_na(y));
  }
}
