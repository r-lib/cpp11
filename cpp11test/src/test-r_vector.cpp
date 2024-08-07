#include "cpp11/integers.hpp"
#include "cpp11/list.hpp"
#include "cpp11/protect.hpp"

#include <testthat.h>

context("r_vector-C++") {
  test_that("writable vector temporary isn't leaked (integer) (#338)") {
    R_xlen_t before = cpp11::detail::store::count();

    // +1 from `x` allocation
    cpp11::writable::integers x(1);

    // Calls move assignment operator `operator=(r_vector<T>&& rhs)`
    // +1 from `rhs` allocation and move into `x`
    // -1 from old `x` release
    x = cpp11::writable::integers(1);

    R_xlen_t after = cpp11::detail::store::count();

    expect_true(before == 0);
    expect_true(after - before == 1);
  }

  test_that("writable vector temporary isn't leaked (list) (#338)") {
    R_xlen_t before = cpp11::detail::store::count();

    // +1 from `x` allocation
    cpp11::writable::list x(1);

    // Calls move assignment operator `operator=(r_vector<T>&& rhs)`
    // +1 from `rhs` allocation and move into `x`
    // -1 from old `x` release
    x = cpp11::writable::list(1);

    R_xlen_t after = cpp11::detail::store::count();

    expect_true(before == 0);
    expect_true(after - before == 1);
  }

  test_that("read-only vector copy constructor doesn't clear properties (#365)") {
    R_xlen_t before = cpp11::detail::store::count();

    SEXP x = PROTECT(Rf_allocVector(INTSXP, 1));
    INTEGER(x)[0] = 1;

    // +1 from `y` creation
    cpp11::integers y(x);

    // Calls read only copy constructor
    // No duplication of `y`'s data is done
    // +1 when adding `z`'s protection to the data
    cpp11::integers z(y);

    R_xlen_t after = cpp11::detail::store::count();

    // `y` properties have not been cleared
    expect_true(y.data() != R_NilValue);
    expect_true(y.size() == 1);

    // `z` owns them now
    expect_true(z.data() != R_NilValue);
    expect_true(z.size() == 1);

    // And these are the same! This is all read-only, so no need to duplicate
    expect_true(z.data() == y.data());

    expect_true(before == 0);
    expect_true(after - before == 2);

    UNPROTECT(1);
  }

  test_that("read-only vector move constructor clears properties (#365)") {
    R_xlen_t before = cpp11::detail::store::count();

    SEXP x = PROTECT(Rf_allocVector(INTSXP, 1));
    INTEGER(x)[0] = 1;

    // +1 from `y` creation
    cpp11::integers y(x);

    // Calls read only move constructor
    // +0 when moving
    cpp11::integers z(std::move(y));

    R_xlen_t after = cpp11::detail::store::count();

    // `y` properties have been cleared in the move
    expect_true(y.data() == R_NilValue);
    expect_true(y.size() == 0);

    // `z` owns them now
    expect_true(z.data() != R_NilValue);
    expect_true(z.size() == 1);

    expect_true(before == 0);
    expect_true(after - before == 1);

    UNPROTECT(1);
  }

  test_that("writable vector copy constructor does not clear properties (#365)") {
    R_xlen_t before = cpp11::detail::store::count();

    // +1 from `y` allocation
    cpp11::writable::integers y(1);

    // Calls writable copy constructor
    // +1 from duplicating `y` and protecting result
    cpp11::writable::integers z(y);

    R_xlen_t after = cpp11::detail::store::count();

    // `y` properties have not been cleared
    expect_true(y.data() != R_NilValue);
    expect_true(y.size() == 1);

    // `z` is a duplicate of `y`
    expect_true(z.data() != R_NilValue);
    expect_true(z.size() == 1);

    // And these are not the same! This is writable, so a duplication occurred.
    expect_true(z.data() != y.data());

    expect_true(before == 0);
    expect_true(after - before == 2);
  }

  test_that("writable vector move constructor clears properties (#365)") {
    R_xlen_t before = cpp11::detail::store::count();

    // +1 from `y` allocation
    cpp11::writable::integers y(1);

    // Calls writable move constructor
    // +0 when moving
    cpp11::writable::integers z(std::move(y));

    R_xlen_t after = cpp11::detail::store::count();

    // `y` properties have been cleared in the move
    expect_true(y.data() == R_NilValue);
    expect_true(y.size() == 0);

    // `z` owns them now
    expect_true(z.data() != R_NilValue);
    expect_true(z.size() == 1);

    expect_true(before == 0);
    expect_true(after - before == 1);
  }

  test_that("read-only vector copy assignment operator doesn't clear properties (#365)") {
    R_xlen_t before = cpp11::detail::store::count();

    SEXP x = PROTECT(Rf_allocVector(INTSXP, 1));
    INTEGER(x)[0] = 1;

    // +1 from `y` creation
    cpp11::integers y(x);

    // +0 for default constructor
    cpp11::integers z;

    expect_true(z.data() == R_NilValue);
    expect_true(z.size() == 0);

    // Calls read only copy assignment operator `operator=(const r_vector<T>& rhs)`
    // +1 from additional protection of `y` (but not duplicating `y`'s data)
    z = y;

    R_xlen_t after = cpp11::detail::store::count();

    // `y` properties have not been cleared
    expect_true(y.data() != R_NilValue);
    expect_true(y.size() == 1);

    // `z` properties have been updated
    expect_true(z.data() != R_NilValue);
    expect_true(z.size() == 1);

    // And these are the same! This is all read-only, so no need to duplicate
    expect_true(z.data() == y.data());

    expect_true(before == 0);
    expect_true(after - before == 2);

    UNPROTECT(1);
  }

  test_that("read-only vector move assignment operator clears properties (#365)") {
    R_xlen_t before = cpp11::detail::store::count();

    SEXP x = PROTECT(Rf_allocVector(INTSXP, 1));
    INTEGER(x)[0] = 1;

    // +1 from `y` creation
    cpp11::integers y(x);

    // +0 for default constructor
    cpp11::integers z;

    // Calls read only move assignment operator `operator=(r_vector<T>&& rhs)`
    // +0 when moving
    z = std::move(y);

    R_xlen_t after = cpp11::detail::store::count();

    // `y` properties have been cleared in the move
    expect_true(y.data() == R_NilValue);
    expect_true(y.size() == 0);

    expect_true(before == 0);
    expect_true(after - before == 1);

    UNPROTECT(1);
  }

  test_that("writable vector copy assignment operator doesn't clear properties (#365)") {
    R_xlen_t before = cpp11::detail::store::count();

    // +1 from `y` allocation
    cpp11::writable::integers y(1);

    // +0 for default constructor
    cpp11::writable::integers z;

    expect_true(z.data() == R_NilValue);
    expect_true(z.size() == 0);

    // Calls writable copy assignment operator `operator=(const r_vector<T>& rhs)`
    // +1 from protecting duplicate of `y`
    z = y;

    R_xlen_t after = cpp11::detail::store::count();

    // `y` properties have not been cleared
    expect_true(y.data() != R_NilValue);
    expect_true(y.size() == 1);

    // `z` properties have been updated
    expect_true(z.data() != R_NilValue);
    expect_true(z.size() == 1);

    // And these are not the same, we made a duplicate
    expect_true(z.data() != y.data());

    expect_true(before == 0);
    expect_true(after - before == 2);
  }

  test_that("writable vector move assignment operator clears properties (#365)") {
    R_xlen_t before = cpp11::detail::store::count();

    // +1 from `y` allocation
    cpp11::writable::integers y(1);

    // +0 for default constructor
    cpp11::writable::integers z;

    // Calls writable move assignment operator `operator=(r_vector<T>&& rhs)`
    // +0 when moving (also clears `capacity` in this case)
    z = std::move(y);

    R_xlen_t after = cpp11::detail::store::count();

    // `y` properties have been cleared in the move
    expect_true(y.data() == R_NilValue);
    expect_true(y.size() == 0);

    expect_true(before == 0);
    expect_true(after - before == 1);
  }

  test_that("writable vector copy constructor correctly tracks the `capacity_`") {
    cpp11::writable::integers x(2);
    x[0] = 1;
    x[1] = 2;

    // Doubles the capacity from 2 to 4
    x.push_back(3);

    // Calls writable copy constructor.
    // Should duplicate without truncations and retain same capacity.
    cpp11::writable::integers y(x);

    // In the past, we truncated (i.e. to size 3) but retained the same capacity of 4,
    // so this could try to push without first resizing.
    y.push_back(4);

    expect_true(y[0] == 1);
    expect_true(y[1] == 2);
    expect_true(y[2] == 3);
    expect_true(y[3] == 4);
  }
}
