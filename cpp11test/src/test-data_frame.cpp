#include "cpp11/data_frame.hpp"
#include "cpp11/function.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/strings.hpp"

#include <testthat.h>

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
    // From bare list
    SEXP x = PROTECT(Rf_allocVector(VECSXP, 0));
    cpp11::data_frame x_df(x);
    expect_true(x_df.nrow() == 0);
    UNPROTECT(1);

    // From bare list with `R_RowNamesSymbol`
    SEXP y = PROTECT(Rf_allocVector(VECSXP, 0));
    SEXP y_row_names = PROTECT(Rf_allocVector(INTSXP, 2));
    SET_INTEGER_ELT(y_row_names, 0, NA_INTEGER);
    SET_INTEGER_ELT(y_row_names, 1, 0);
    Rf_setAttrib(y, R_RowNamesSymbol, y_row_names);
    cpp11::data_frame y_df(y);
    expect_true(y_df.nrow() == 0);
    UNPROTECT(2);

    // From classed data frame with `R_RowNamesSymbol`
    SEXP z = PROTECT(Rf_allocVector(VECSXP, 0));
    SEXP z_row_names = PROTECT(Rf_allocVector(INTSXP, 2));
    SET_INTEGER_ELT(z_row_names, 0, NA_INTEGER);
    SET_INTEGER_ELT(z_row_names, 1, 0);
    Rf_setAttrib(z, R_RowNamesSymbol, z_row_names);
    SEXP z_class = PROTECT(Rf_allocVector(STRSXP, 1));
    SET_STRING_ELT(z_class, 0, Rf_mkChar("data.frame"));
    Rf_setAttrib(z, R_ClassSymbol, z_class);
    cpp11::data_frame z_df(z);
    expect_true(z_df.nrow() == 0);
    UNPROTECT(3);
  }

  test_that("writable::data_frame::nrow works with 0x0 dfs") {
    using namespace cpp11::literals;

    // From bare list
    SEXP x = PROTECT(Rf_allocVector(VECSXP, 0));
    cpp11::writable::data_frame x_df(x);
    expect_true(x_df.nrow() == 0);
    UNPROTECT(1);

    // From bare list with `R_RowNamesSymbol`
    cpp11::writable::list y(0_xl);
    y.attr(R_RowNamesSymbol) = {NA_INTEGER, 0};
    cpp11::writable::data_frame y_df(y);
    expect_true(y_df.nrow() == 0);

    // From classed data frame with `R_RowNamesSymbol`
    cpp11::writable::list z(0_xl);
    z.attr(R_RowNamesSymbol) = {NA_INTEGER, 0};
    z.attr(R_ClassSymbol) = "data.frame";
    cpp11::writable::data_frame z_df(z);
    expect_true(z_df.nrow() == 0);
  }

  test_that("data_frame::nrow works with 10x0 dfs") {
    // From bare list with `R_RowNamesSymbol`
    SEXP y = PROTECT(Rf_allocVector(VECSXP, 0));
    SEXP y_row_names = PROTECT(Rf_allocVector(INTSXP, 2));
    SET_INTEGER_ELT(y_row_names, 0, NA_INTEGER);
    SET_INTEGER_ELT(y_row_names, 1, 10);
    Rf_setAttrib(y, R_RowNamesSymbol, y_row_names);
    cpp11::data_frame y_df(y);
    expect_true(y_df.nrow() == 10);
    UNPROTECT(2);

    // From classed data frame with `R_RowNamesSymbol`
    SEXP z = PROTECT(Rf_allocVector(VECSXP, 0));
    SEXP z_row_names = PROTECT(Rf_allocVector(INTSXP, 2));
    SET_INTEGER_ELT(z_row_names, 0, NA_INTEGER);
    SET_INTEGER_ELT(z_row_names, 1, 10);
    Rf_setAttrib(z, R_RowNamesSymbol, z_row_names);
    SEXP z_class = PROTECT(Rf_allocVector(STRSXP, 1));
    SET_STRING_ELT(z_class, 0, Rf_mkChar("data.frame"));
    Rf_setAttrib(z, R_ClassSymbol, z_class);
    cpp11::data_frame z_df(z);
    expect_true(z_df.nrow() == 10);
    UNPROTECT(3);
  }

  test_that("writable::data_frame::nrow works with 10x0 dfs (#272)") {
    using namespace cpp11::literals;

    // From bare list with `R_RowNamesSymbol`
    cpp11::writable::list y(0_xl);
    y.attr(R_RowNamesSymbol) = {NA_INTEGER, 10};
    cpp11::writable::data_frame y_df(y);
    expect_true(y_df.nrow() == 10);

    // From classed data frame with `R_RowNamesSymbol`
    cpp11::writable::list z(0_xl);
    z.attr(R_RowNamesSymbol) = {NA_INTEGER, 10};
    z.attr(R_ClassSymbol) = "data.frame";
    cpp11::writable::data_frame z_df(z);
    expect_true(z_df.nrow() == 10);

    // Manually specify `nrow` using special constructor
    bool is_altrep = false;
    SEXP x = PROTECT(Rf_allocVector(VECSXP, 0));
    cpp11::writable::data_frame df(x, is_altrep, 10);
    expect_true(df.nrow() == 10);
    UNPROTECT(1);
  }

  test_that("data_frame::nrow works with 0x1 dfs") {
    // From bare list
    SEXP x = PROTECT(Rf_allocVector(VECSXP, 1));
    SET_VECTOR_ELT(x, 0, Rf_allocVector(INTSXP, 0));
    cpp11::data_frame x_df(x);
    expect_true(x_df.nrow() == 0);
    UNPROTECT(1);
  }

  test_that("writable::data_frame::nrow works with 0x1 dfs") {
    // From bare list
    SEXP x = PROTECT(Rf_allocVector(VECSXP, 1));
    SET_VECTOR_ELT(x, 0, Rf_allocVector(INTSXP, 0));
    cpp11::writable::data_frame x_df(x);
    expect_true(x_df.nrow() == 0);
    UNPROTECT(1);
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
