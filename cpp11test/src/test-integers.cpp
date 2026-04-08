#include "cpp11/R.hpp"
#include "cpp11/doubles.hpp"
#include "cpp11/function.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/logicals.hpp"
#include "cpp11/strings.hpp"

#include <testthat.h>

context("integers-C++") {
  test_that("as_integers(doubles)") {
    // r_typeof(x) == INTSXP
    cpp11::writable::doubles y;
    y.push_back(10.00);
    cpp11::writable::integers i(cpp11::as_integers(y));
    expect_true(i[0] == 10);
    expect_true(cpp11::detail::r_typeof(i) == INTSXP);

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
    expect_true(cpp11::detail::r_typeof(t) == INTSXP);

    cpp11::writable::doubles na{NA_REAL, 42.};
    cpp11::integers na2(cpp11::as_integers(na));
    expect_true(cpp11::is_na(na2[0]));
    expect_true(!cpp11::is_na(na2[1]));
  }

  test_that("as_integers(logicals)") {
    cpp11::writable::logicals y;

    for (int i = 0; i < 4; i++) {
      y.push_back(i % 2 == 0);
    }

    cpp11::integers i(cpp11::as_integers(y));

    expect_true(i[0] == 1);
    expect_true(i[1] == 0);
    expect_true(i[2] == 1);
    expect_true(i[3] == 0);
    expect_true(cpp11::detail::r_typeof(i) == INTSXP);
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

  test_that("writable::integers(initializer_list<named_arg>)") {
    using namespace cpp11::literals;

    SEXP x1 = PROTECT(Rf_allocVector(INTSXP, 1));
    SEXP x2 = PROTECT(Rf_allocVector(INTSXP, 1));
    SEXP x3 = PROTECT(Rf_allocVector(INTSXP, 1));

    SET_INTEGER_ELT(x1, 0, 0);
    SET_INTEGER_ELT(x2, 0, 5);
    SET_INTEGER_ELT(x3, 0, NA_INTEGER);

    // From scalar integer vectors
    cpp11::writable::integers x({"one"_nm = x1, "two"_nm = x2, "three"_nm = x3});
    expect_true(x.named());
    expect_true(x["one"] == 0);
    expect_true(x["two"] == 5);
    expect_true(x["three"] == NA_INTEGER);

    // From ints
    cpp11::writable::integers y({"one"_nm = 0, "two"_nm = 5, "three"_nm = NA_INTEGER});
    expect_true(y.named());
    expect_true(y["one"] == 0);
    expect_true(y["two"] == 5);
    expect_true(y["three"] == NA_INTEGER);

    UNPROTECT(3);
  }

  test_that("writable::integers(initializer_list<named_arg>) type check") {
    using namespace cpp11::literals;
    expect_error_as(cpp11::writable::integers({"one"_nm = true}), cpp11::type_error);
    expect_error_as(cpp11::writable::integers({"one"_nm = R_NilValue}),
                    cpp11::type_error);
  }

  test_that("writable::integers(initializer_list<named_arg>) length check") {
    using namespace cpp11::literals;
    SEXP x = PROTECT(Rf_allocVector(INTSXP, 2));
    expect_error_as(cpp11::writable::integers({"x"_nm = x}), std::length_error);
    UNPROTECT(1);
  }

  test_that("writable::integers(initializer_list<int>)") {
    cpp11::writable::integers x({1, 2, 3});
    expect_true(x[0] == 1);
    expect_true(x[1] == 2);
    expect_true(x[2] == 3);
  }

#if defined(__APPLE__)
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

  test_that("operator[] and at with names") {
    using namespace cpp11::literals;
    cpp11::writable::integers x({"a"_nm = 1, "b"_nm = 2});
    cpp11::integers y(x);

    expect_true(x["a"] == 1);
    expect_true(x["b"] == 2);
    expect_error(x["c"]);

    expect_true(x.at("a") == 1);
    expect_true(x.at("b") == 2);
    expect_error(x.at("c"));

    expect_true(y["a"] == 1);
    expect_true(y["b"] == 2);
    expect_error(y["c"]);

    expect_true(y.at("a") == 1);
    expect_true(y.at("b") == 2);
    expect_error(y.at("c"));
  }

  test_that("is_na(integer)") {
    int x = 0;
    expect_true(!cpp11::is_na(x));

    int y = NA_INTEGER;
    expect_true(cpp11::is_na(y));
  }
}
