#include <cstring>
#include "cpp11/sexp.hpp"
#include "cpp11/strings.hpp"

#include <testthat.h>

context("strings-C++") {
  test_that("strings.push_back()") {
    cpp11::writable::strings x;
    x.push_back("a");
    x.push_back("b");

    expect_true(x.size() == 2);
    expect_true(x[0] == "a");
    expect_true(x[1] == "b");
  }
  test_that("strings.resize()") {
    cpp11::writable::strings x;
    x.resize(2);
    x[0] = "a";
    x[1] = "b";

    expect_true(x.size() == 2);
    expect_true(x[0] == "a");
    expect_true(x[1] == "b");
  }
  test_that("strings.at()") {
    cpp11::writable::strings x;

    expect_error(x.at(-1));

    expect_error(x.at(0));

    x.push_back("a");
    auto test = x.at(0);
    expect_true(test == "a");
    expect_error(x.at(1));
  }
  test_that("strings.pop_back()") {
    cpp11::writable::strings x;

    x.push_back("a");
    x.push_back("b");
    x.pop_back();

    expect_true(x.size() == 1);
    expect_true(x[0] == "a");

    expect_error(x.at(1));
  }
  test_that("strings.insert()") {
    cpp11::writable::strings x;

    x.insert(0, "a");
    x.insert(0, "b");
    x.insert(1, "c");
    expect_true(x.size() == 3);

    expect_true(x[0] == "b");
    expect_true(x[1] == "c");
    expect_true(x[2] == "a");
  }

  test_that("strings.erase()") {
    cpp11::writable::strings x;

    x.push_back("a");
    x.push_back("b");
    x.push_back("c");
    x.push_back("d");
    x.push_back("e");

    expect_true(x.size() == 5);

    x.erase(0);

    expect_true(x.size() == 4);
    expect_true(x[0] == "b");
    expect_true(x[1] == "c");
    expect_true(x[2] == "d");
    expect_true(x[3] == "e");

    x.erase(2);

    expect_true(x.size() == 3);
    expect_true(x[0] == "b");
    expect_true(x[1] == "c");
    expect_true(x[2] == "e");
  }

  test_that("strings.iterator* = ") {
    cpp11::writable::strings x;
    x.push_back("a");
    x.push_back("b");
    x.push_back("c");
    auto it = x.begin() + 1;
    *it = "d";
    ++it;
    *it = "e";

    expect_true(x.size() == 3);
    expect_true(x[0] == "a");
    expect_true(x[1] == "d");
    expect_true(x[2] == "e");
  }

  test_that("writable::strings(SEXP)") {
    SEXP x = PROTECT(Rf_allocVector(STRSXP, 5));

    SET_STRING_ELT(x, 0, Rf_mkCharCE("a", CE_UTF8));
    SET_STRING_ELT(x, 1, Rf_mkCharCE("b", CE_UTF8));
    SET_STRING_ELT(x, 2, Rf_mkCharCE("c", CE_UTF8));
    SET_STRING_ELT(x, 3, Rf_mkCharCE("d", CE_UTF8));
    SET_STRING_ELT(x, 4, Rf_mkCharCE("e", CE_UTF8));

    cpp11::writable::strings y(x);
    y[0] = "foo";

    expect_true(x != y.data());

    expect_true(std::string(CHAR(STRING_ELT(x, 0))) == "a");
    expect_true(y[0] == "foo");

    cpp11::writable::strings z(y);
    z[0] = "bar";

    expect_true(z.data() != y.data());

    expect_true(std::string(CHAR(STRING_ELT(x, 0))) == "a");
    expect_true(y[0] == "foo");
    expect_true(z[0] == "bar");

    UNPROTECT(1);
  }

  test_that("writable::strings(initializer_list<named_arg>)") {
    using namespace cpp11::literals;

    SEXP x1 = PROTECT(Rf_allocVector(STRSXP, 1));
    SEXP x2 = PROTECT(Rf_allocVector(STRSXP, 1));
    SEXP x3 = PROTECT(Rf_allocVector(STRSXP, 1));

    SEXP one = PROTECT(Rf_mkCharCE("one", CE_UTF8));
    SEXP two = PROTECT(Rf_mkCharCE("two", CE_UTF8));
    SEXP three = PROTECT(Rf_mkCharCE("three", CE_UTF8));

    SET_STRING_ELT(x1, 0, one);
    SET_STRING_ELT(x2, 0, two);
    SET_STRING_ELT(x3, 0, three);

    // From scalar string vectors
    cpp11::writable::strings x({"one"_nm = x1, "two"_nm = x2, "three"_nm = x3});
    expect_true(x.named());
    expect_true(x["one"] == cpp11::r_string("one"));
    expect_true(x["two"] == cpp11::r_string("two"));
    expect_true(x["three"] == cpp11::r_string("three"));

    // From strings
    cpp11::writable::strings y(
        {"one"_nm = "one", "two"_nm = "two", "three"_nm = "three"});
    expect_true(y.named());
    expect_true(y["one"] == cpp11::r_string("one"));
    expect_true(y["two"] == cpp11::r_string("two"));
    expect_true(y["three"] == cpp11::r_string("three"));

    UNPROTECT(6);
  }

  test_that("writable::strings(initializer_list<named_arg>) type check") {
    using namespace cpp11::literals;
    expect_error_as(cpp11::writable::strings({"one"_nm = true}), cpp11::type_error);
    expect_error_as(cpp11::writable::strings({"one"_nm = R_NilValue}), cpp11::type_error);
  }

  test_that("writable::strings(initializer_list<named_arg>) length check") {
    using namespace cpp11::literals;
    SEXP x = PROTECT(Rf_allocVector(STRSXP, 2));
    expect_error_as(cpp11::writable::strings({"x"_nm = x}), std::length_error);
    UNPROTECT(1);
  }

  test_that("writable::strings(initializer_list<r_string>)") {
    cpp11::r_string abc = cpp11::r_string("abc");
    cpp11::r_string na = cpp11::r_string(NA_STRING);

    cpp11::writable::strings x({abc, na, abc});
    expect_true(x[0] == abc);
    expect_true(x[1] == na);
    expect_true(x[2] == abc);

    // This works due to implicit conversion of `SEXP` to `r_string`
    SEXP a = PROTECT(Rf_mkCharCE("a", CE_UTF8));
    SEXP b = PROTECT(Rf_mkCharCE("b", CE_UTF8));
    cpp11::writable::strings y({a, b});
    expect_true(y[0] == cpp11::r_string("a"));
    expect_true(y[1] == cpp11::r_string("b"));

    // This works due to implicit conversion of `const char*` to `r_string`
    cpp11::writable::strings z({"neat", "stuff"});
    expect_true(z[0] == cpp11::r_string("neat"));
    expect_true(z[1] == cpp11::r_string("stuff"));

    cpp11::writable::strings w({std::string("neat"), std::string("stuff")});
    expect_true(w[0] == cpp11::r_string("neat"));
    expect_true(w[1] == cpp11::r_string("stuff"));

    UNPROTECT(2);
  }

  test_that("std::initializer_list<const char*>") {
    cpp11::writable::strings x{"foo"};
    expect_true(x.size() == 1);
    expect_true(x[0] == "foo");
  }

  test_that("std::initializer_list<std::string>") {
    std::string str("foo");
    cpp11::writable::strings x{str};
    expect_true(x.size() == 1);
    expect_true(x[0] == "foo");
  }

  test_that("NA_STRING constructor") {
    cpp11::writable::strings x({NA_STRING});

    expect_true(x.size() == 1);
    expect_true(x[0] == NA_STRING);

    cpp11::writable::strings y({NA_STRING, "foo"});

    expect_true(y.size() == 2);
    expect_true(y[0] == NA_STRING);
    expect_true(y[1] == "foo");
  }

  test_that("CHARSXP move constructor") {
    SEXP x = PROTECT(Rf_mkChar("foo"));
    cpp11::writable::strings y(std::move(x));

    expect_true(y.size() == 1);
    expect_true(y[0] == "foo");
    UNPROTECT(1);
  }

  // test_that("strings::operator=() and strings::at() do not compile") {
  // cpp11::strings x(Rf_mkChar("foo"));

  // x[0] = "bar";
  // x.at(0) = "bar";
  //}

  test_that("strings::operator=() and strings::at() do compile") {
    cpp11::writable::strings x(Rf_mkChar("foo"));
    x[0] = "bar";
    x.at(0) = "bar";
    expect_true(x[0] == Rf_mkChar("bar"));
  }

  test_that("strings::operator=() works with std:strings") {
    cpp11::writable::strings x(Rf_mkChar("foo"));
    std::string y("bar");

    x[0] = y;
    expect_true(x[0] == y);
  }

  test_that("conversion to SEXP with missing values") {
    cpp11::sexp x1 = cpp11::r_string(NA_STRING);
    expect_true(static_cast<SEXP>(x1) == NA_STRING);

    cpp11::sexp x2 = cpp11::writable::strings(NA_STRING);
    expect_true(Rf_xlength(x2) == 1);
    expect_true(STRING_ELT(x2, 0) == NA_STRING);

    cpp11::sexp x3 = cpp11::writable::strings({NA_STRING});
    expect_true(Rf_xlength(x3) == 1);
    expect_true(STRING_ELT(x3, 0) == NA_STRING);

    cpp11::sexp x4 = cpp11::writable::strings({NA_STRING, "text"});
    expect_true(Rf_xlength(x4) == 2);
    expect_true(STRING_ELT(x4, 0) == NA_STRING);
    expect_true(strcmp(CHAR(STRING_ELT(x4, 1)), "text") == 0);
  }
}
