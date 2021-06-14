#include <testthat.h>
#include "cpp11/nas.hpp"
#include "cpp11/logicals.hpp"
#include "cpp11/r_bool.hpp"
#include "cpp11/r_vector.hpp"
#include "cpp11/r_string.hpp"


context("nas-C++") {
  test_that("na integer") {
    expect_true(cpp11::na<int>::value == NA_INTEGER);
  }
  test_that("na double") {
    expect_true(ISNA(cpp11::na<double>::value));
  }
  test_that("na bool") {
    expect_true(cpp11::na<cpp11::r_bool>::value == NA_LOGICAL);

  }
  test_that("na string") {
    expect_true(cpp11::na<cpp11::r_string>::value == NA_STRING);
  }
}
