#include "cpp11/strings.hpp"

#include <testthat.h>

context("string-C++") {
  test_that("is_na(string)") {
    cpp11::r_string x("foo");
    expect_true(!cpp11::is_na(x));

    cpp11::r_string y(NA_STRING);
    expect_true(cpp11::is_na(y));
  }
}
