#include <testthat.h>
#include "cpp11/doubles.hpp"
#include "cpp11/function.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/matrix.hpp"

context("matrix-C++") {
  test_that("matrix works") {
    cpp11::writable::doubles_matrix x(5, 2);

    cpp11::integers dim(SEXP(x.attr("dim")));

    expect_true(dim[0] == 5);
    expect_true(dim[1] == 2);

    expect_true(x.nrow() == 5);
    expect_true(x.ncol() == 2);
  }
  test_that("matrix works") {
    auto getExportedValue = cpp11::package("base")["getExportedValue"];

    cpp11::doubles_matrix x(SEXP(getExportedValue("datasets", "volcano")));

    expect_true(x.size() == 5307);
    expect_true(x.nrow() == 87);
    expect_true(x.ncol() == 61);
  }
}
