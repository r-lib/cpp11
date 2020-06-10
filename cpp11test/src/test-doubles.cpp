#include <testthat.h>
#include <cstring>
#include "cpp11/doubles.hpp"
#include "cpp11/sexp.hpp"

context("doubles-C++") {
  test_that("doubles::vector()") {
    cpp11::doubles x(Rf_allocVector(REALSXP, 2));
    expect_true(x.size() == 2);

    expect_error(cpp11::doubles(Rf_allocVector(INTSXP, 2)));
  }
  test_that("doubles.push_back()") {
    cpp11::writable::doubles x;
    x.push_back(1);
    x.push_back(2);

    expect_true(x.size() == 2);
    expect_true(x[0] == 1);
    expect_true(x[1] == 2);
  }
  test_that("doubles.resize()") {
    cpp11::writable::doubles x;
    x.resize(2);
    x[0] = 1;
    x[1] = 2;

    expect_true(x.size() == 2);
    expect_true(x[0] == 1);
    expect_true(x[1] == 2);
  }
  test_that("doubles.at()") {
    cpp11::writable::doubles x;

    expect_error(x.at(-1));

    expect_error(x.at(0));

    x.push_back(1);
    expect_true(x.at(0) == 1);
    expect_error(x.at(1));
  }
  test_that("doubles.pop_back()") {
    cpp11::writable::doubles x;

    x.push_back(1);
    x.push_back(2);
    x.pop_back();

    expect_true(x.size() == 1);
    expect_true(x[0] == 1);

    expect_error(x.at(1));
  }
  test_that("doubles.insert()") {
    cpp11::writable::doubles x;

    x.insert(0, 1);
    x.insert(0, 2);
    x.insert(1, 3);
    expect_true(x.size() == 3);

    expect_true(x[0] == 2);
    expect_true(x[1] == 3);
    expect_true(x[2] == 1);
  }
  test_that("doubles.erase()") {
    cpp11::writable::doubles x;

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
  test_that("doubles.iterator* = ") {
    cpp11::writable::doubles x;
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

  test_that("writable::doubles(SEXP)") {
    SEXP x = PROTECT(Rf_allocVector(REALSXP, 5));

    REAL(x)[0] = 1;
    REAL(x)[1] = 2;
    REAL(x)[2] = 3;
    REAL(x)[3] = 4;
    REAL(x)[4] = 5;

    cpp11::writable::doubles y(x);
    y[0] = -1;

    expect_true(x != y.data());

    expect_true(REAL(x)[0] == 1);
    expect_true(y[0] == -1);

    cpp11::writable::doubles z(y);
    z[0] = -2;

    expect_true(z.data() != y.data());

    expect_true(REAL(x)[0] == 1);
    expect_true(y[0] == -1);
    expect_true(z[0] == -2);

    UNPROTECT(1);
  }

#if defined(__APPLE__) && defined(R_VERSION) && R_VERSION >= R_Version(3, 5, 0)
  test_that("writable::doubles(ALTREP_SEXP)") {
    SEXP x = PROTECT(Rf_coerceVector(R_compact_intrange(1, 5), REALSXP));
    // Need to find (or create) an altrep class that implements duplicate.

    cpp11::writable::doubles y(x);
    y[0] = -1;

    expect_true(x != y.data());

    expect_true(REAL_ELT(x, 0) == 1);
    expect_true(y[0] == -1);

    cpp11::writable::doubles z(y);
    z[0] = -2;

    expect_true(z.data() != y.data());

    expect_true(REAL_ELT(x, 0) == 1);
    expect_true(y[0] == -1);
    expect_true(z[0] == -2);

    z.push_back(6);
    expect_true(z[5] == 6);

    UNPROTECT(1);
  }

  test_that("writable::doubles(SEXP) assignment") {
    cpp11::writable::doubles x({1., 2., 3.});
    cpp11::writable::doubles y({0.});
    y = x;
    expect_true(y.size() == 3);
    expect_true(y.data() != x.data());
    expect_true(y.is_altrep() == x.is_altrep());

    cpp11::writable::doubles z(
        Rf_coerceVector(R_compact_intrange(1, 5), REALSXP));
    cpp11::writable::doubles w({0.});
    w = z;
    expect_true(w.size() == 5);
    expect_true(w.data() != z.data());
    expect_true(w.is_altrep() == z.is_altrep());
  }

  test_that("writable::doubles(SEXP) move assignment") {
    cpp11::writable::doubles x({1., 2., 3.});
    cpp11::writable::doubles y({0.});
    auto x_data = x.data();

    y = std::move(x);
    expect_true(y.size() == 3);
    expect_true(y.data() == x_data);
    expect_true(y.is_altrep() == false);

    cpp11::writable::doubles z(
        Rf_coerceVector(R_compact_intrange(1, 5), REALSXP));
    cpp11::writable::doubles w({0.});
    expect_true(z.is_altrep() == true);

    auto z_data = z.data();
    w = std::move(z);
    expect_true(w.size() == 5);
    expect_true(w.data() == z_data);
    expect_true(w.is_altrep() == true);
  }

#endif

  test_that("doubles::names") {
    using namespace cpp11::literals;
    cpp11::writable::doubles x({"a"_nm = 1., "b"_nm = 2.});
    expect_true(x[0] == 1.);
    expect_true(x[1] == 2.);

    expect_true(x["a"] == 1.);
    expect_true(x["b"] == 2.);

    cpp11::sexp nms(x.names());
    expect_true(Rf_xlength(nms) == 2);
    auto nms0 = CHAR(STRING_ELT(nms, 0));
    auto nms1 = CHAR(STRING_ELT(nms, 1));
    expect_true(strcmp(nms0, "a") == 0);
    expect_true(strcmp(nms1, "b") == 0);
  }

  test_that("doubles::attr") {
    cpp11::doubles x(PROTECT(Rf_allocVector(REALSXP, 2)));
    REAL(x)[0] = 1;
    REAL(x)[1] = 2;

    SEXP foo = Rf_install("foo");
    Rf_setAttrib(x, foo, Rf_mkString("bar"));

    // This doesn't compile by design
    // x.attr("foo") = "bar";

    // But this will
    cpp11::writable::doubles y(x);
    y.attr("foo") = "baz";

    expect_true(strcmp(CHAR(STRING_ELT(x.attr("foo"), 0)), "bar") == 0);
    expect_true(strcmp(CHAR(STRING_ELT(y.attr("foo"), 0)), "baz") == 0);

    UNPROTECT(1);
  }

  test_that("writable::doubles(std::vector::iterator)") {
    std::vector<double> x({1, 2, 3, 4, 5});
    cpp11::writable::doubles y(x.begin(), x.end());
    expect_true(y.size() == 5);
    expect_true(y[0] == 1);
    expect_true(y[4] == 5);
  }

  test_that("writable::doubles(std::vector)") {
    std::vector<double> x({1, 2, 3, 4, 5});
    cpp11::writable::doubles y(x);
    expect_true(y.size() == 5);
    expect_true(y[0] == 1);
    expect_true(y[4] == 5);
  }
}
