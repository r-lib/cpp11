#include "cpp11/doubles.hpp"
#include "cpp11/list.hpp"
#include "cpp11/list_of.hpp"
#include "cpp11/strings.hpp"

#include <testthat.h>

context("list_of-C++") {
  test_that("list_of works") {
    using namespace cpp11::literals;

    cpp11::writable::list x({"x"_nm = cpp11::writable::doubles({1., 2., 3.}),
                             "y"_nm = cpp11::writable::doubles({4., 5., 6.})});

    cpp11::list_of<cpp11::doubles> res(x);

    expect_true(res.size() == 2);
    expect_true(res[0][0] == 1.);
    expect_true(res[1][0] == 4.);
    expect_true(res.names()[0] == "x");
    expect_true(res.names()[1] == "y");
  }

  test_that("writable::list_of works") {
    using namespace cpp11::literals;

    cpp11::writable::list x({"x"_nm = cpp11::writable::doubles({1., 2., 3.}),
                             "y"_nm = cpp11::writable::doubles({4., 5., 6.})});

    cpp11::writable::list_of<cpp11::writable::doubles> res(x);

    res.push_back({"z"_nm = cpp11::writable::doubles({7., 8., 9.})});

    expect_true(res.size() == 3);
    expect_true(REAL(VECTOR_ELT(res, 2))[0] == 7.);

    res[0][0] = 2.;

    expect_true(REAL(VECTOR_ELT(res, 0))[0] == 2.);

    res[1] = cpp11::writable::doubles({7., 8., 9.});

    expect_true(REAL(res[1])[0] == 7.);
    expect_true(REAL(res[1])[1] == 8.);
    expect_true(REAL(res[1])[2] == 9.);

    res["x"][0] = 4;
    expect_true(REAL(res[0])[0] == 4.);
  }
}
