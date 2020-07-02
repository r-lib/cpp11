#include <testthat.h>
#include "cpp11/doubles.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/list.hpp"
#include "cpp11/logicals.hpp"
#include "cpp11/raws.hpp"
#include "cpp11/strings.hpp"

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
    cpp11::writable::list x(
        {cpp11::writable::doubles({1, 2, 3}), cpp11::writable::strings({"x", "y", "z"})});

    x.attr("names") = cpp11::writable::strings({"x", "y"});
    x.attr("class") = "data.frame";
    x.attr("rownames") = cpp11::writable::doubles({-3, NA_REAL});

    expect_true(Rf_inherits(x, "data.frame"));
  }
}
