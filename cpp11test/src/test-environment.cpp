#include "headers/as.hpp"
#include "headers/environment.hpp"
#include "headers/function.hpp"
#include "headers/strings.hpp"

#include <testthat.h>

context("environment-C++") {
  test_that("environment works") {
    auto new_env = cpp11::package("base")["new.env"];
    SEXP x_sxp = PROTECT(new_env());

    cpp11::environment x(x_sxp);

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

    expect_true(static_cast<SEXP>(x) == x_sxp);

    UNPROTECT(1);
  }
}
