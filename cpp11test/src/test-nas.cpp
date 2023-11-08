#include "headers/doubles.hpp"
#include "headers/integers.hpp"
#include "headers/r_bool.hpp"
#include "headers/r_string.hpp"

#include <testthat.h>

context("nas-C++") {
  test_that("na integer") { expect_true(cpp11::na<int>() == NA_INTEGER); }
  test_that("na double") { expect_true(ISNA(cpp11::na<double>())); }
  test_that("na bool") { expect_true(cpp11::na<cpp11::r_bool>() == NA_LOGICAL); }
  test_that("na string") { expect_true(cpp11::na<cpp11::r_string>() == NA_STRING); }
}
