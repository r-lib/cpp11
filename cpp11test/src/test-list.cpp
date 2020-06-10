#include <testthat.h>
#include "cpp11/strings.hpp"
#include "cpp11/doubles.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/list.hpp"
#include "cpp11/logicals.hpp"
#include "cpp11/raws.hpp"

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

    cpp11::logicals forth(x[3]);
    expect_true(forth[0] == TRUE);
    expect_true(forth[1] == FALSE);
    expect_true(forth[2] == TRUE);

    cpp11::raws fifth(x[4]);
    expect_true(fifth[0] == 'a');
    expect_true(fifth[1] == 'b');
    expect_true(fifth[2] == 'c');
  }

  test_that("attribute setting works") {
    cpp11::writable::list x({cpp11::writable::doubles({1, 2, 3}),
                               cpp11::writable::strings({"x", "y", "z"})});

    x.attr("names") = cpp11::writable::strings({"x", "y"});
    x.attr("class") = "data.frame";
    x.attr("rownames") = cpp11::writable::doubles({-3, NA_REAL});

    expect_true(Rf_inherits(x, "data.frame"));
  }
}

// test_that("strings.resize()") {
// cpp11::writable::strings x;
// x.resize(2);
// x[0] = "a";
// x[1] = "b";

// expect_true(x.size() == 2);
// expect_true(x[0] == "a");
// expect_true(x[1] == "b");
//}
// test_that("strings.at()") {
// cpp11::writable::strings x;

// expect_error(x.at(-1));

// expect_error(x.at(0));

// x.push_back("a");
// expect_true(x.at(0) == "a");
// expect_error(x.at(1));
//}
// test_that("strings.pop_back()") {
// cpp11::writable::strings x;

// x.push_back("a");
// x.push_back("b");
// x.pop_back();

// expect_true(x.size() == 1);
// expect_true(x[0] == "a");

// expect_error(x.at(1));
//}
// test_that("strings.insert()") {
// cpp11::writable::strings x;

// x.insert(0, "a");
// x.insert(0, "b");
// x.insert(1, "c");
// expect_true(x.size() == 3);

// expect_true(x[0] == "b");
// expect_true(x[1] == "c");
// expect_true(x[2] == "a");
//}

// test_that("strings.erase()") {
// cpp11::writable::strings x;

// x.push_back("a");
// x.push_back("b");
// x.push_back("c");
// x.push_back("d");
// x.push_back("e");

// expect_true(x.size() == 5);

// x.erase(0);

// expect_true(x.size() == 4);
// expect_true(x[0] == "b");
// expect_true(x[1] == "c");
// expect_true(x[2] == "d");
// expect_true(x[3] == "e");

// x.erase(2);

// expect_true(x.size() == 3);
// expect_true(x[0] == "b");
// expect_true(x[1] == "c");
// expect_true(x[2] == "e");
//}

// test_that("strings.iterator* = ") {
// cpp11::writable::strings x;
// x.push_back("a");
// x.push_back("b");
// x.push_back("c");
// auto it = x.begin() + 1;
//*it = "d";
//++it;
//*it = "e";

// expect_true(x.size() == 3);
// expect_true(x[0] == "a");
// expect_true(x[1] == "d");
// expect_true(x[2] == "e");
//}

// test_that("writable::strings(SEXP)") {
// SEXP x = PROTECT(Rf_allocVector(STRSXP, 5));

// SET_STRING_ELT(x, 0, Rf_mkCharCE("a", CE_UTF8));
// SET_STRING_ELT(x, 1, Rf_mkCharCE("b", CE_UTF8));
// SET_STRING_ELT(x, 2, Rf_mkCharCE("c", CE_UTF8));
// SET_STRING_ELT(x, 3, Rf_mkCharCE("d", CE_UTF8));
// SET_STRING_ELT(x, 4, Rf_mkCharCE("e", CE_UTF8));

// cpp11::writable::strings y(x);
// y[0] = "foo";

// expect_true(x != y.data());

// expect_true(std::string(CHAR(STRING_ELT(x, 0))) == "a");
// expect_true(y[0] == "foo");

// cpp11::writable::strings z(y);
// z[0] = "bar";

// expect_true(z.data() != y.data());

// expect_true(std::string(CHAR(STRING_ELT(x, 0))) == "a");
// expect_true(y[0] == "foo");
// expect_true(z[0] == "bar");

// UNPROTECT(1);
//}

//// test_that("writable::strings(ALTREP_SEXP)") {
//// SEXP x = PROTECT(R_compact_uint8_trange(1, 5));
////// Need to find (or create) an altrep class that implements duplicate.

//// cpp11::writable::strings y(x);
//// y[0] = -1;

//// expect_true(x != y.data());

//// expect_true(raw_ELT(x, 0) == 1);
//// expect_true(y[0] == -1);

//// cpp11::writable::strings z(y);
//// z[0] = -2;

//// expect_true(z.data() != y.data());

//// expect_true(raw_ELT(x, 0) == 1);
//// expect_true(y[0] == -1);
//// expect_true(z[0] == -2);

//// z.push_back(6);
//// expect_true(z[5] == 6);

//// UNPROTECT(1);
////}
//}
