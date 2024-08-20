#include "cpp11/R.hpp"
#include "cpp11/doubles.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/list.hpp"
#include "cpp11/logicals.hpp"
#include "cpp11/protect.hpp"
#include "cpp11/raws.hpp"
#include "cpp11/strings.hpp"

#include <testthat.h>

context("list-C++") {
  test_that("list.push_back()") {
    cpp11::writable::list x;

    x.push_back(cpp11::writable::doubles({1.}));
    x.push_back(cpp11::writable::integers({3, 4, 5}));
    x.push_back(cpp11::writable::strings({"foo", "bar"}));

    cpp11::writable::logicals lgl;
    lgl.push_back(TRUE);
    lgl.push_back(FALSE);
    lgl.push_back(TRUE);
    x.push_back(lgl);

    x.push_back(cpp11::writable::raws({'a', 'b', 'c'}));

    expect_true(x.size() == 5);

    cpp11::doubles first(x[0]);
    expect_true(first[0] == 1.);

    cpp11::integers second(x[1]);
    expect_true(second[0] == 3);
    expect_true(second[1] == 4);
    expect_true(second[2] == 5);

    cpp11::strings third(x[2]);
    expect_true(third[0] == "foo");
    expect_true(third[1] == "bar");

    cpp11::logicals fourth(x[3]);
    expect_true(fourth[0] == TRUE);
    expect_true(fourth[1] == FALSE);
    expect_true(fourth[2] == TRUE);

    cpp11::raws fifth(x[4]);
    expect_true(fifth[0] == 'a');
    expect_true(fifth[1] == 'b');
    expect_true(fifth[2] == 'c');
  }

  test_that("unnamed_list.push_back(unnamed_arg)") {
    cpp11::writable::list x(1);
    x.push_back(cpp11::writable::integers(2));

    expect_true(x.names() == R_NilValue);
  }

  test_that("unnamed_list.push_back(named_arg)") {
    using namespace cpp11::literals;

    cpp11::writable::list x(1);
    x.push_back("bar"_nm = 2);

    cpp11::strings nms(x.names());

    expect_true(nms.size() == 2);
    expect_true(nms[0] == "");
    expect_true(nms[1] == "bar");
  }

  test_that("named_list.push_back(unnamed_arg)") {
    using namespace cpp11::literals;

    cpp11::writable::list x({"foo"_nm = 1});
    x.push_back(cpp11::writable::integers(2));

    cpp11::strings nms(x.names());

    expect_true(nms.size() == 2);
    expect_true(nms[0] == "foo");
    expect_true(nms[1] == "");
  }

  test_that("named_list.push_back(named_arg)") {
    using namespace cpp11::literals;

    cpp11::writable::list x({"foo"_nm = 1});
    x.push_back({"bar"_nm = 2});

    cpp11::strings nms(x.names());

    expect_true(nms.size() == 2);
    expect_true(nms[0] == "foo");
    expect_true(nms[1] == "bar");
  }

  test_that("empty_list.push_back(unnamed_arg)") {
    cpp11::writable::list x;
    x.push_back(cpp11::writable::integers(2));

    expect_true(x.names() == R_NilValue);
  }

  test_that("empty_list.push_back(named_arg)") {
    using namespace cpp11::literals;

    cpp11::writable::list x;
    x.push_back({"bar"_nm = 2});

    cpp11::strings nms(x.names());

    expect_true(nms.size() == 1);
    expect_true(nms[0] == "bar");
  }

  test_that("attribute setting works") {
    cpp11::writable::list x(
        {cpp11::writable::doubles({1, 2, 3}), cpp11::writable::strings({"x", "y", "z"})});

    x.attr("names") = cpp11::writable::strings({"x", "y"});
    x.attr("class") = "data.frame";
    x.attr("rownames") = cpp11::writable::doubles({-3, NA_REAL});

    expect_true(Rf_inherits(x, "data.frame"));
  }

  test_that("list::iterator uses VECTOR_ELT") {
    cpp11::writable::list x({cpp11::writable::integers({1, 2})});
    cpp11::integers first(*x.begin());
    expect_true(first[0] == 1);
    expect_true(first[1] == 2);
  }

  test_that("list.named() works") {
    using namespace cpp11::literals;

    cpp11::writable::list x({"bar"_nm = 2});
    expect_true(x.named());

    cpp11::writable::list y(1);
    expect_false(y.named());
  }

  test_that("list.empty() works") {
    cpp11::writable::list x;

    expect_true(x.empty());

    cpp11::writable::list y(1);

    expect_false(y.empty());
  }

  test_that("names of named lists are also resized") {
    using namespace cpp11::literals;

    cpp11::writable::list x;
    x.push_back({"n1"_nm = 1});
    x.push_back({"n2"_nm = 2});
    x.push_back({"n3"_nm = 3});
    x.push_back({"n4"_nm = 4});
    x.push_back({"n5"_nm = 5});
    x = SEXP(x);

    cpp11::strings nms(x.names());
    expect_true(x.size() == nms.size());
  }

  test_that("list::operator[] and at by name") {
    SEXP x = PROTECT(Rf_allocVector(VECSXP, 1));

    SEXP elt = Rf_allocVector(INTSXP, 1);
    SET_VECTOR_ELT(x, 0, elt);
    SET_INTEGER_ELT(elt, 0, 1);

    SEXP names = Rf_allocVector(STRSXP, 1);
    Rf_setAttrib(x, R_NamesSymbol, names);
    SET_STRING_ELT(names, 0, Rf_mkCharCE("name", CE_UTF8));

    cpp11::list lst(x);

    expect_true(lst.named());
    expect_true(lst["name"] == elt);
    expect_true(lst.at("name") == elt);

    // Lists are the only class where OOB accesses by name return `NULL`
    expect_true(lst["oob"] == R_NilValue);
    expect_true(lst.at("oob") == R_NilValue);

    UNPROTECT(1);
  }

  test_that("We don't return NULL for default constructed vectors") {
    cpp11::writable::list x;
    SEXP y(x);

    expect_true(Rf_xlength(y) == 0);
    expect_true(y != R_NilValue);
  }

  test_that("writable::list(initializer_list<named_arg>)") {
    using namespace cpp11::literals;

    SEXP x1 = PROTECT(Rf_allocVector(INTSXP, 1));
    SEXP x2 = PROTECT(Rf_allocVector(REALSXP, 2));
    SEXP x3 = PROTECT(Rf_allocVector(STRSXP, 3));

    // Note that `x1`, `x2`, and `x3` are list elements, not lists of length 1!
    cpp11::writable::list x({"one"_nm = x1, "two"_nm = x2, "three"_nm = x3});
    expect_true(x.named());
    expect_true(x["one"] == x1);
    expect_true(x["two"] == x2);
    expect_true(x["three"] == x3);

    // This also works, with varying types
    cpp11::writable::list y({"one"_nm = 1, "two"_nm = true, "three"_nm = 2.5});
    expect_true(y.named());
    expect_true(cpp11::detail::r_typeof(y["one"]) == INTSXP);
    expect_true(cpp11::detail::r_typeof(y["two"]) == LGLSXP);
    expect_true(cpp11::detail::r_typeof(y["three"]) == REALSXP);

    UNPROTECT(3);
  }

  test_that("writable::list(initializer_list<SEXP>)") {
    SEXP x1 = PROTECT(Rf_allocVector(INTSXP, 1));
    SEXP x2 = PROTECT(Rf_allocVector(REALSXP, 2));
    SEXP x3 = PROTECT(Rf_allocVector(STRSXP, 3));

    cpp11::writable::list x({x1, x2, x3});
    expect_true(x[0] == x1);
    expect_true(x[1] == x2);
    expect_true(x[2] == x3);

    UNPROTECT(3);
  }
}
