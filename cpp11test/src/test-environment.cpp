#include "cpp11/as.hpp"
#include "cpp11/environment.hpp"
#include "cpp11/function.hpp"
#include "cpp11/strings.hpp"

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
    // Object must exist in the environment when we convert to SEXP
    auto bar_proxy = x["bar"];
    expect_error_as(static_cast<SEXP>(bar_proxy), cpp11::unwind_exception);

    x.remove("foo");
    expect_true(x.size() == 0);
    // Object must exist in the environment when we convert to SEXP
    auto foo_proxy = x["foo"];
    expect_error_as(static_cast<SEXP>(foo_proxy), cpp11::unwind_exception);

    expect_true(static_cast<SEXP>(x) == x_sxp);

    UNPROTECT(1);
  }

  test_that("environment doesn't leak `R_MissingArg`") {
    auto new_env = cpp11::package("base")["new.env"];
    SEXP x_sxp = PROTECT(new_env());

    // Install `R_MissingArg` as a value in the environment
    Rf_defineVar(Rf_install("missing"), R_MissingArg, x_sxp);

    cpp11::environment x(x_sxp);
    expect_true(x.size() == 1);

    // Upon conversion to SEXP, we error on `R_MissingArg`.
    // Base R's `R_getVar()` tries hard not to leak this, so we do too.
    auto proxy = x["missing"];
    expect_error_as(static_cast<SEXP>(proxy), cpp11::unwind_exception);

    UNPROTECT(1);
  }
}
