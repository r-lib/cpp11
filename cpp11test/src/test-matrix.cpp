#include "cpp11/doubles.hpp"
#include "cpp11/function.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/matrix.hpp"

#include <testthat.h>

context("matrix-C++") {
  test_that("matrix dim attributes are correct for writable matrices") {
    cpp11::writable::doubles_matrix x(5, 2);

    cpp11::integers dim(SEXP(x.attr("dim")));

    expect_true(dim[0] == 5);
    expect_true(dim[1] == 2);

    expect_true(x.nrow() == 5);
    expect_true(x.ncol() == 2);
  }
  test_that("matrix dim attributes are correct for read only matrices") {
    auto getExportedValue = cpp11::package("base")["getExportedValue"];

    cpp11::doubles_matrix x(SEXP(getExportedValue("datasets", "volcano")));

    expect_true(x.size() == 5307);
    expect_true(x.nrow() == 87);
    expect_true(x.ncol() == 61);
  }

  test_that("row based subsetting works") {
    auto getExportedValue = cpp11::package("base")["getExportedValue"];

    cpp11::doubles_matrix x(SEXP(getExportedValue("datasets", "volcano")));

    auto r = x[0];
    expect_true(r[0] == 100);
    expect_true(r[60] == 103);
  }

  test_that("index based subsetting works") {
    auto getExportedValue = cpp11::package("base")["getExportedValue"];

    cpp11::doubles_matrix x(SEXP(getExportedValue("datasets", "volcano")));

    expect_true(x(0, 0) == 100);
    expect_true(x(0, 60) == 103);
  }

  test_that("copy constructor works") {
    auto getExportedValue = cpp11::package("base")["getExportedValue"];
    cpp11::doubles_matrix x(SEXP(getExportedValue("datasets", "volcano")));
    cpp11::doubles_matrix y(x);

    expect_true(x.nrow() == y.nrow());
    expect_true(SEXP(x) == SEXP(y));
  }
}
