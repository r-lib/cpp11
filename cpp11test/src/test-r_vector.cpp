#include "cpp11/integers.hpp"
#include "cpp11/list.hpp"
#include "cpp11/protect.hpp"
#include "cpp11/strings.hpp"

#include <testthat.h>

#include <algorithm>  // for max_element

#ifdef _WIN32
#include "Rversion.h"
#define CPP11_HAS_IS_UTILITIES R_VERSION >= R_Version(4, 0, 0)
#else
#define CPP11_HAS_IS_UTILITIES 1
#endif

#if CPP11_HAS_IS_UTILITIES
context("r_vector-capabilities-C++") {
  test_that("read only vector capabilities") {
    using cpp11::integers;

    expect_true(std::is_destructible<integers>::value);
    expect_true(std::is_default_constructible<integers>::value);
    expect_true(std::is_nothrow_default_constructible<integers>::value);
    expect_true(std::is_copy_constructible<integers>::value);
    expect_true(std::is_move_constructible<integers>::value);
    expect_true(std::is_copy_assignable<integers>::value);
    expect_true(std::is_move_assignable<integers>::value);
  }

  test_that("writable vector capabilities") {
    using cpp11::writable::integers;

    expect_true(std::is_destructible<integers>::value);
    expect_true(std::is_default_constructible<integers>::value);
    expect_true(std::is_nothrow_default_constructible<integers>::value);
    expect_true(std::is_copy_constructible<integers>::value);
    expect_true(std::is_move_constructible<integers>::value);
    expect_true(std::is_copy_assignable<integers>::value);
    expect_true(std::is_move_assignable<integers>::value);
  }

  test_that("read only const_iterator capabilities") {
    using cpp11::integers;

    expect_true(std::is_destructible<integers::const_iterator>::value);
    expect_true(std::is_trivially_destructible<integers::const_iterator>::value);
    expect_true(std::is_copy_constructible<integers::const_iterator>::value);
    expect_true(std::is_move_constructible<integers::const_iterator>::value);
    expect_true(std::is_copy_assignable<integers::const_iterator>::value);
    expect_true(std::is_trivially_copy_assignable<integers::const_iterator>::value);
    expect_true(std::is_move_assignable<integers::const_iterator>::value);
    expect_true(std::is_trivially_move_assignable<integers::const_iterator>::value);
  }

  test_that("writable iterator capabilities") {
    using cpp11::writable::integers;

    expect_true(std::is_destructible<integers::iterator>::value);
    expect_true(std::is_trivially_destructible<integers::iterator>::value);
    expect_true(std::is_copy_constructible<integers::iterator>::value);
    expect_true(std::is_move_constructible<integers::iterator>::value);
    expect_true(std::is_copy_assignable<integers::iterator>::value);
    expect_true(std::is_trivially_copy_assignable<integers::iterator>::value);
    expect_true(std::is_move_assignable<integers::iterator>::value);
    expect_true(std::is_trivially_move_assignable<integers::iterator>::value);
  }

  test_that("writable proxy capabilities") {
    using cpp11::writable::integers;

    expect_true(std::is_destructible<integers::proxy>::value);
    expect_true(std::is_trivially_destructible<integers::proxy>::value);
    expect_true(std::is_copy_constructible<integers::proxy>::value);
    expect_true(std::is_move_constructible<integers::proxy>::value);
    expect_true(std::is_copy_assignable<integers::proxy>::value);
    expect_true(std::is_move_assignable<integers::proxy>::value);
  }
}
#endif

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

  test_that("writable vector copy assignment works with default constructed vectors") {
    // Default constructed - the `data_` is `R_NilValue`!
    cpp11::writable::integers x;

    cpp11::writable::integers y(1);

    // Checks that this guards against calling `INTEGER()` on `R_NilValue`.
    y = x;

    SEXP z(y);
    expect_true(cpp11::detail::r_typeof(z) == INTSXP);
    expect_true(Rf_xlength(z) == 0);
  }

  test_that("writable vector copy constructor correctly tracks the `capacity_`") {
    cpp11::writable::integers x(2);
    x[0] = 1;
    x[1] = 2;

    // Doubles the capacity from 2 to 4
    x.push_back(3);
    expect_true(Rf_xlength(x.data()) == 4);

    // Calls writable copy constructor.
    // Should duplicate without truncations and retain same capacity.
    cpp11::writable::integers y(x);
    expect_true(Rf_xlength(y.data()) == 4);

    // In the past, we truncated (i.e. to size 3) but retained the same capacity of 4,
    // so this could try to push without first resizing.
    y.push_back(4);

    expect_true(y[0] == 1);
    expect_true(y[1] == 2);
    expect_true(y[2] == 3);
    expect_true(y[3] == 4);
  }

  test_that("writable vector copy constructor works with default constructed vectors") {
    // Default constructed - the `data_` is `R_NilValue`!
    cpp11::writable::integers x;

    // Checks that this guards against calling `INTEGER()` on `R_NilValue`.
    cpp11::writable::integers y(x);

    SEXP z(y);
    expect_true(cpp11::detail::r_typeof(z) == INTSXP);
    expect_true(Rf_xlength(z) == 0);
  }

  test_that(
      "read only vector copy constructor from a writable vector correctly truncates") {
    cpp11::writable::integers x(2);
    x[0] = 1;
    x[1] = 2;

    // Doubles the capacity from 2 to 4, meaning the underlying SEXP has length 4 now.
    x.push_back(3);
    expect_true(Rf_xlength(x.data()) == 4);

    // Calls read only copy constructor from a writable vector.
    // Should truncate the SEXP before wrapping in a read only vector.
    cpp11::integers y(x);
    expect_true(Rf_xlength(y.data()) == 3);

    // `x` is still in a good state
    expect_true(x.data() != R_NilValue);
    expect_true(x.size() == 3);

    // Even if we get a temporary writable vector, that goes through the same copy
    // constructor as above, because we still have to truncate before taking ownership.
    cpp11::integers z(std::move(x));
    expect_true(Rf_xlength(z.data()) == 3);

    // So technically `x` is still in a working state after this, although that is
    // implementation defined and up to us to decide on
    expect_true(x.data() != R_NilValue);
    expect_true(x.size() == 3);
  }

  test_that(
      "writable vector truncation resizes names and retains attributes (but not dim or "
      "dim names)") {
    cpp11::writable::integers x(2);
    x[0] = 1;
    x[1] = 2;

    // Doubles the capacity from 2 to 4, meaning the underlying SEXP has length 4 now.
    x.push_back(3);
    expect_true(Rf_xlength(x.data()) == 4);

    // Set some names
    SEXP names = PROTECT(Rf_allocVector(STRSXP, 3));
    SET_STRING_ELT(names, 0, Rf_mkCharCE("x", CE_UTF8));
    SET_STRING_ELT(names, 1, Rf_mkCharCE("y", CE_UTF8));
    SET_STRING_ELT(names, 2, Rf_mkCharCE("z", CE_UTF8));
    x.names() = names;

    // Length of names SEXP is actually 4 now, extended by `setAttrib()` to match
    // the internal capacity
    expect_true(Rf_xlength(Rf_getAttrib(x.data(), R_NamesSymbol)) == 4);

    // Set an attribute
    SEXP bar = PROTECT(Rf_ScalarInteger(1));
    x.attr("foo") = bar;

    // Extract out the underlying SEXP using the operator:
    // - This truncates to size 3
    // - This truncates and keeps names
    // - This copies over attributes like `"foo"`
    // - This updates the internal SEXP in `x` to the one in `x_sexp` (gross but users
    //   probably expect this at this point)
    SEXP x_sexp = x;

    expect_true(Rf_xlength(x_sexp) == 3);
    expect_true(Rf_xlength(Rf_getAttrib(x_sexp, R_NamesSymbol)) == 3);
    expect_true(Rf_getAttrib(x_sexp, Rf_install("foo")) == bar);

    expect_true(x.data() == x_sexp);

    UNPROTECT(2);
  }

  test_that("`proxy` is copy assignable (integers) (#300, #339)") {
    cpp11::writable::integers foo = {1, 2, 3, 4, 5};
    cpp11::writable::integers bar = {6, 7, 8, 9, 10};

    // Using rvalue temporaries (i.e. move assignable, but using copy assignment operator)
    for (R_xlen_t i = 0; i < foo.size(); ++i) {
      bar[i] = foo[i];
    }

    // Using lvalues (i.e. copy assignable)
    cpp11::writable::integers::proxy x = foo[0];
    bar[4] = x;

    expect_true(bar[0] == 1);
    expect_true(bar[1] == 2);
    expect_true(bar[2] == 3);
    expect_true(bar[3] == 4);
    expect_true(bar[4] == 1);
  }

  test_that("`proxy` is copy assignable (list) (#300, #339)") {
    SEXP a = PROTECT(Rf_allocVector(INTSXP, 1));
    SEXP b = PROTECT(Rf_allocVector(REALSXP, 2));

    cpp11::writable::list x({a, b});
    cpp11::writable::list y(2);

    // Using rvalue temporaries (i.e. move assignable, but using copy assignment operator)
    y[0] = x[0];

    // Using lvalues (i.e. copy assignable)
    cpp11::writable::list::proxy elt = x[1];
    y[1] = elt;

    expect_true(y[0] == a);
    expect_true(y[1] == b);

    UNPROTECT(2);
  }

  test_that("`proxy` is copy assignable (strings) (#300, #339)") {
    SEXP a = PROTECT(Rf_mkCharCE("a", CE_UTF8));
    SEXP b = PROTECT(Rf_mkCharCE("b", CE_UTF8));

    cpp11::writable::strings x({a, b});
    cpp11::writable::strings y(2);

    // Using rvalue temporaries (i.e. move assignable, but using copy assignment operator)
    y[0] = x[0];

    // Using lvalues (i.e. copy assignable)
    cpp11::writable::strings::proxy elt = x[1];
    y[1] = elt;

    expect_true(y[0] == a);
    expect_true(y[1] == b);

    UNPROTECT(2);
  }

  test_that("std::max_element works on read only vectors") {
    SEXP foo_sexp = PROTECT(Rf_allocVector(INTSXP, 5));
    SET_INTEGER_ELT(foo_sexp, 0, 1);
    SET_INTEGER_ELT(foo_sexp, 1, 2);
    SET_INTEGER_ELT(foo_sexp, 2, 5);
    SET_INTEGER_ELT(foo_sexp, 3, 4);
    SET_INTEGER_ELT(foo_sexp, 4, 3);
    cpp11::integers foo(foo_sexp);

    auto element = std::max_element(foo.begin(), foo.end());

    expect_true(*element == 5);

    UNPROTECT(1);
  }

  test_that("std::max_element works on writable vectors (#334)") {
    cpp11::writable::integers foo = {1, 2, 5, 4, 3};
    auto element = std::max_element(foo.begin(), foo.end());
    expect_true(*element == 5);
  }
}
