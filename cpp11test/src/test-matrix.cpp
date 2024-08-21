#include "cpp11/doubles.hpp"
#include "cpp11/function.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/matrix.hpp"

#include <testthat.h>

context("matrix-C++") {
  test_that("matrix dim attributes are correct for writable matrices") {
    cpp11::writable::doubles_matrix<cpp11::by_row> x(5, 2);

    cpp11::integers dim(SEXP(x.attr("dim")));

    expect_true(dim[0] == 5);
    expect_true(dim[1] == 2);

    expect_true(x.nrow() == 5);
    expect_true(x.ncol() == 2);
    expect_true(x.nslices() == 5);
    expect_true(x.slice_size() == 2);
    expect_true(x.slice_stride() == 5);
    expect_true(x.slice_offset(0) == 0);
    expect_true(x.slice_offset(1) == 1);
    expect_true(x[1].size() == 2);
    expect_true(x[1].stride() == 5);
  }
  test_that("matrix dim attributes are correct for read only matrices") {
    auto getExportedValue = cpp11::package("base")["getExportedValue"];

    test_that("matrix<by_row> attributes are correct") {
      cpp11::doubles_matrix<cpp11::by_row> x(getExportedValue("datasets", "volcano"));

      expect_true(x.size() == 5307);
      expect_true(x.nrow() == 87);
      expect_true(x.ncol() == 61);
      expect_true(x.nslices() == 87);
      expect_true(x.slice_size() == 61);
      expect_true(x.slice_stride() == 87);
      expect_true(x.slice_offset(0) == 0);
      expect_true(x.slice_offset(1) == 1);
      expect_true(x[1].size() == 61);
      expect_true(x[1].stride() == 87);
    }
    test_that("matrix<by_column> attributes are correct") {
      cpp11::doubles_matrix<cpp11::by_column> x(getExportedValue("datasets", "volcano"));

      expect_true(x.size() == 5307);
      expect_true(x.nrow() == 87);
      expect_true(x.ncol() == 61);
      expect_true(x.nslices() == 61);
      expect_true(x.slice_size() == 87);
      expect_true(x.slice_stride() == 1);
      expect_true(x.slice_offset(0) == 0);
      expect_true(x.slice_offset(1) == 87);
      expect_true(x[1].size() == 87);
      expect_true(x[1].stride() == 1);
    }
  }

  test_that("row based subsetting works") {
    auto getExportedValue = cpp11::package("base")["getExportedValue"];

    cpp11::doubles_matrix<cpp11::by_row> x(getExportedValue("datasets", "volcano"));
    expect_true(x.nslices() == 87);
    expect_true(x.slice_size() == 61);

    auto r = x[0];
    expect_true(r[0] == 100);
    expect_true(r[60] == 103);

    auto r2 = x[2];
    expect_true(r2[0] == 102);
    expect_true(r2[60] == 104);
  }

  test_that("column based subsetting works") {
    auto getExportedValue = cpp11::package("base")["getExportedValue"];

    cpp11::doubles_matrix<cpp11::by_column> x(getExportedValue("datasets", "volcano"));
    expect_true(x.nslices() == 61);
    expect_true(x.slice_size() == 87);

    auto c = x[0];
    expect_true(c[0] == 100);
    expect_true(c[86] == 97);

    auto c2 = x[5];
    expect_true(c2[0] == 101);
    expect_true(c2[86] == 99);
  }

  test_that("index based subsetting works") {
    auto getExportedValue = cpp11::package("base")["getExportedValue"];

    cpp11::doubles_matrix<cpp11::by_row> xr(getExportedValue("datasets", "volcano"));
    expect_true(xr(0, 0) == 100);
    expect_true(xr(0, 60) == 103);
    expect_true(xr(10, 13) == 121);

    cpp11::doubles_matrix<cpp11::by_column> xc(getExportedValue("datasets", "volcano"));
    expect_true(xc(0, 0) == 100);
    expect_true(xc(0, 60) == 103);
    expect_true(xc(10, 13) == 121);
  }

  test_that("copy constructor works for read only matrices") {
    auto getExportedValue = cpp11::package("base")["getExportedValue"];
    cpp11::doubles_matrix<cpp11::by_row> x(getExportedValue("datasets", "volcano"));

    cpp11::doubles_matrix<cpp11::by_row> yr(x);
    expect_true(x.nrow() == yr.nrow());
    expect_true(x.ncol() == yr.ncol());
    expect_true(yr.nslices() == yr.nrow());
    expect_true(SEXP(x) == SEXP(yr));

    cpp11::doubles_matrix<cpp11::by_column> yc(x);
    expect_true(x.nrow() == yc.nrow());
    expect_true(x.ncol() == yc.ncol());
    expect_true(yc.nslices() == yc.ncol());
    expect_true(SEXP(x) == SEXP(yc));
  }

  test_that("copy constructor works for writable matrices") {
    cpp11::writable::doubles_matrix<cpp11::by_row> x(5, 2);

    auto x_dim = x.attr("dim");
    expect_true(INTEGER_ELT(x_dim, 0) == 5);
    expect_true(INTEGER_ELT(x_dim, 1) == 2);

    cpp11::writable::doubles_matrix<cpp11::by_row> yr(x);
    expect_true(x.nrow() == yr.nrow());
    expect_true(x.ncol() == yr.ncol());
    expect_true(yr.nslices() == yr.nrow());
    // Note that a copy should be made when copying writable!
    expect_true(SEXP(x) != SEXP(yr));

    // TODO: Fix this
    // // `dim` attribute is retained on copy
    // auto yr_dim = yr.attr("dim");
    // expect_true(INTEGER_ELT(yr_dim, 0) == 5);
    // expect_true(INTEGER_ELT(yr_dim, 1) == 2);

    cpp11::writable::doubles_matrix<cpp11::by_column> yc(x);
    expect_true(x.nrow() == yc.nrow());
    expect_true(x.ncol() == yc.ncol());
    expect_true(yc.nslices() == yc.ncol());
    // Note that a copy should be made when copying writable!
    expect_true(SEXP(x) != SEXP(yc));

    // TODO: Fix this
    // // `dim` attribute is retained on copy
    // auto yc_dim = yc.attr("dim");
    // expect_true(INTEGER_ELT(yc_dim, 0) == 5);
    // expect_true(INTEGER_ELT(yc_dim, 1) == 2);
  }

  test_that("copy constructor is not enabled across vector types") {
    cpp11::writable::doubles_matrix<cpp11::by_row> x(5, 2);
    expect_error(cpp11::writable::integers_matrix<cpp11::by_column>(x));
  }
}
