#include <testthat.h>

#include "cpp11/as.hpp"
#include "cpp11/environment.hpp"
#include "cpp11/function.hpp"

context("environment-C++") {
  test_that("environment works") {
    auto new_env = cpp11::package("base")["new.env"];
    cpp11::environment x(new_env());

    x["foo"] = 1;
    expect_true(cpp11::as_cpp<int>(x["foo"]) == 1);
  }
}
