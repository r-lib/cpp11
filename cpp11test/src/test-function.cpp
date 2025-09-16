#include "cpp11/function.hpp"

#include <testthat.h>

context("function-C++") {
  test_that("functions can be called") {
    auto median = cpp11::package("stats")["median"];
    double res = median(cpp11::as_sexp({1., 2., 3., NA_REAL}), true);
    expect_true(res == 2.);

    double res2 = median(cpp11::as_sexp({1., 2., 3., NA_REAL}), false);
    expect_true(ISNAN(res2));
  }

  test_that("functions can be called with named arguments") {
    using namespace cpp11::literals;

    auto median = cpp11::package("stats")["median"];
    double res = median("x"_nm = {1., 2., 3., NA_REAL}, "na.rm"_nm = true);
    expect_true(res == 2.);

    double res2 = median(cpp11::as_sexp({1., 2., 3., NA_REAL}), false);
    expect_true(ISNAN(res2));
  }

  test_that("base functions can be called") {
    auto file = cpp11::package("base")["file"];
    auto isOpen = cpp11::package("base")["isOpen"];
    auto close = cpp11::package("base")["close"];

    cpp11::sexp con = file("foo");

    bool res = isOpen(con);

    expect_true(res == false);

    close(con);
  }

  test_that("unknown packages cause an error (#317)") {
    expect_error_as(cpp11::package("definitely_not_a_package"), cpp11::unwind_exception);
  }
}
