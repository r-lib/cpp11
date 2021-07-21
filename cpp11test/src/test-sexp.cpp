#include "cpp11/list.hpp"

#include <testthat.h>

context("sexp-C++") {
  test_that("sexp initializer lists work") {
    using namespace cpp11::literals;
    cpp11::writable::list out({
        "int"_nm = {1, 2, 3},
        "dbl"_nm = {1., 2., 3.},
        "char"_nm = {"x", "y", "z"},
    });

    out.attr("class") = "data.frame";
    out.attr("row.names") = {NA_INTEGER, -3};

    expect_true(Rf_inherits(out, "data.frame"));
  }

  test_that("scalar constructors work") {
    using namespace cpp11::literals;
    cpp11::writable::list out({
        "int"_nm = 1,
        "dbl"_nm = 1.,
        "char"_nm = "x",
    });

    out.attr("class") = "data.frame";
    out.attr("row.names") = {NA_INTEGER, -1};

    expect_true(Rf_inherits(out, "data.frame"));
  }

  test_that("move constructor works") {
    using namespace cpp11::literals;
    cpp11::sexp x(Rf_ScalarReal(5.));
    cpp11::sexp y(std::move(x));

    expect_true(SEXP(x) == R_NilValue);
    expect_true(REAL(y)[0] == 5.);
  }
}
