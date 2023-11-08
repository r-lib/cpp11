#include "headers/function.hpp"
#include "headers/protect.hpp"
#include "testthat.h"

#ifdef HAS_UNWIND_PROTECT

/*
 * See https://github.com/r-lib/cpp11/pull/327 for full details.
 *
 * - `cpp11::package("cpp11test")["test_destruction_outer"]` uses
 *   `unwind_protect()` to call R level `test_destruction_outer()` but no entry
 *   macros are set up. Instead we are going to catch exceptions that get here
 *   with `expect_error_as()`.
 *
 *   - Call R level `test_destruction_outer()` to set up `BEGIN_CPP11` /
 *     `END_CPP11` entry macros.
 *
 *   - C++ `test_destruction_outer()` goes through `unwind_protect()` to call
 *     the R level `test_destruction_inner()`.
 *
 *     - R level `test_destruction_inner()` sets up its own `BEGIN_CPP11` /
 *       `END_CPP11` entry macros.
 *
 *     - C++ `test_destruction_inner()` goes through `unwind_protect()` to call
 *       `Rf_error()` (i.e., we are nested within `unwind_protect()`s!).
 *
 *     - `longjmp()` is caught from inner `unwind_protect()`, and an exception
 *       is thrown which is caught by the inner entry macros, allowing us to run
 *       the destructor of `x`, then we let R continue the unwind process.
 *
 *   - This `longjmp()`s again and is caught by the outer `unwind_protect()`, an
 *     exception is thrown which is caught by the outer entry macros, and we let
 *     R continue the unwind process one more time.
 *
 * - This `longjmp()` is caught by `cpp11::package()`'s `unwind_protect()`,
 *   an exception is thrown, and that is caught by `expect_error_as()`.
 */

// Global variable to detect if the destructor has been run or not
static bool destructed = false;

class HasDestructor {
 public:
  ~HasDestructor();
};

HasDestructor::~HasDestructor() {
  // Destructor has run!
  destructed = true;
}

[[cpp11::register]] void test_destruction_inner() {
  // Expect that `x`'s destructor gets to run on the way out
  HasDestructor x{};
  cpp11::stop("oh no!");
}

[[cpp11::register]] void test_destruction_outer() {
  const auto test_destruction_inner =
      cpp11::package("cpp11test")["test_destruction_inner"];
  test_destruction_inner();
}

context("unwind_protect-nested-C++") {
  test_that(
      "nested `unwind_protect()` (with entry macros set up) will run destructors"
      "(#327)") {
    const auto fn = [&] {
      const auto test_destruction_outer =
          cpp11::package("cpp11test")["test_destruction_outer"];
      test_destruction_outer();
    };

    expect_error_as(fn(), cpp11::unwind_exception);
    expect_true(destructed);

    destructed = false;
  }
}

#endif
