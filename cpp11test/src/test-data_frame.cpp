#include <testthat.h>
#include "cpp11/data_frame.hpp"
#include "cpp11/function.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/strings.hpp"

context("data_frame-C++") {
  test_that("data_frame works") {
    auto getExportedValue = cpp11::package("base")["getExportedValue"];
    auto mtcars = getExportedValue("datasets", "mtcars");
    cpp11::data_frame mtcars_df(mtcars);

    expect_true(mtcars_df.nrow() == 32);
    expect_true(mtcars_df.ncol() == 11);

    cpp11::strings names(mtcars_df.names());
    expect_true(names[0] == "mpg");
    expect_true(names[7] == "vs");

    auto iris = getExportedValue("datasets", "iris");
    cpp11::data_frame iris_df(iris);

    expect_true(iris_df.nrow() == 150);
    expect_true(iris_df.ncol() == 5);
  }

  test_that("data_frame::nrow works with 0x0 dfs") {
    SEXP x = PROTECT(Rf_allocVector(VECSXP, 0));

    cpp11::data_frame df(x);
    expect_true(df.nrow() == 0);

    UNPROTECT(1);
  }

  test_that("data_frame::nrow works with 10x0 dfs") {
    using namespace cpp11::literals;
    cpp11::writable::list x(0_xl);
    x.attr(R_RowNamesSymbol) = {NA_INTEGER, -10};

    cpp11::data_frame df(x);
    expect_true(df.nrow() == 10);
  }

  test_that("writable::data_frame works") {
    using namespace cpp11::literals;
    cpp11::writable::data_frame df({"x"_nm = {1, 2, 3}, "y"_nm = {"a", "b", "c"}});
    auto nrows = df.nrow();
    expect_true(df.nrow() == 3);
    expect_true(df.ncol() == 2);

    cpp11::strings names(df.names());
    expect_true(names[0] == "x");
    expect_true(names[1] == "y");

    cpp11::integers x(df[0]);
    expect_true(x[0] == 1);
    expect_true(x[1] == 2);
    expect_true(x[2] == 3);

    cpp11::strings y(df[1]);
    expect_true(y[0] == "a");
    expect_true(y[1] == "b");
    expect_true(y[2] == "c");

    SEXP out = df;

    std::string clazz(
        Rf_translateCharUTF8(STRING_ELT(Rf_getAttrib(out, R_ClassSymbol), 0)));
    expect_true(clazz == "data.frame");

    cpp11::integers row_names(Rf_getAttrib(out, R_RowNamesSymbol));
    expect_true(row_names[0] == 1);
    expect_true(row_names[1] == 2);
    expect_true(row_names[2] == 3);
  }

  test_that("can set attributes on a data_frame") {
    using namespace cpp11::literals;

    cpp11::writable::data_frame df({"x"_nm = {1, 2, 3}, "y"_nm = {"a", "b", "c"}});

    df.attr("foo") = "bar";

    cpp11::r_string foo = cpp11::strings(df.attr("foo"))[0];
    expect_true(foo == "bar");

    df.names() = {"a", "b"};

    expect_true(cpp11::integers(df["a"])[0] == 1);
    expect_true(cpp11::strings(df["b"])[2] == "c");
  }

  test_that("growing vectors uses proper length") {
    using namespace cpp11::literals;

    cpp11::writable::integers x, y;
    for (int i = 0; i < 10; ++i) {
      x.push_back(i);
      y.push_back(i);
    }
    cpp11::writable::data_frame out({"x"_nm = x, "y"_nm = y});

    expect_true(out.nrow() == 10);
  }
}
