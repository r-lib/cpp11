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

  using namespace cpp11::literals;
  test_that("unnamed_list.push_back(unnamed_arg)") {
    cpp11::writable::list x(1);
    x.push_back(cpp11::writable::integers(2));

    expect_true(x.names() == R_NilValue);
  }

  test_that("unnamed_list.push_back(named_arg)") {
    cpp11::writable::list x(1);
    x.push_back("bar"_nm = 2);

    cpp11::strings nms(x.names());

    expect_true(nms.size() == 2);
    expect_true(nms[0] == "");
    expect_true(nms[1] == "bar");
  }

  test_that("named_list.push_back(unnamed_arg)") {
    cpp11::writable::list x({"foo"_nm = 1});
    x.push_back(cpp11::writable::integers(2));

    cpp11::strings nms(x.names());

    expect_true(nms.size() == 2);
    expect_true(nms[0] == "foo");
    expect_true(nms[1] == "");
  }

  test_that("named_list.push_back(named_arg)") {
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

  test_that("We don't return NULL for default constructed vectors") {
    cpp11::writable::list x;
    SEXP y(x);

    expect_true(Rf_xlength(y) == 0);
    expect_true(y != R_NilValue);
  }
}
