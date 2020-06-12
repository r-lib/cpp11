#include <testthat.h>

#include "cpp11/as.hpp"
#include "cpp11/environment.hpp"
#include "cpp11/function.hpp"
#include "cpp11/strings.hpp"

context("environment-C++") {
  test_that("environment works") {
    auto new_env = cpp11::package("base")["new.env"];
    cpp11::environment x(new_env());

    expect_true(x.size() == 0);

    x["foo"] = 1;
    expect_true(x.size() == 1);
    expect_true(cpp11::as_cpp<int>(x["foo"]) == 1);

    x["bar"] = "hi";
    expect_true(x.size() == 2);
    expect_true(cpp11::strings(x["bar"])[0] == "hi");

    x.remove("bar");
    expect_true(x.size() == 1);
    expect_true(x["bar"] == R_UnboundValue);

    x.remove("foo");
    expect_true(x.size() == 0);
    expect_true(x["foo"] == R_UnboundValue);
  }
}
