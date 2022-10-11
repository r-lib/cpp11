#include <iostream>
#include "cpp11/external_pointer.hpp"

#include <testthat.h>

bool deleted = false;

void deleter(int* ptr) {
  deleted = true;
  delete ptr;
}

context("external_pointer-C++") {
  test_that("external_pointer works") {
    std::vector<int>* v = new std::vector<int>;
    v->push_back(1);
    v->push_back(2);

    cpp11::external_pointer<std::vector<int>> p(v);

    expect_true(p->at(0) == 1);
    expect_true(p->at(1) == 2);

    p.release();

    // Double release should be a no-op
    p.release();

    expect_true(p.get() == nullptr);
  }

  test_that("external_pointer works with a custom deleter") {
    deleted = false;
    cpp11::external_pointer<int, deleter> uniq(new int);
    expect_true(deleted == false);
    uniq.reset();
    expect_true(deleted == true);
  }

  test_that("can set and get tag") {
    cpp11::external_pointer<int> extptr(new int);
    SEXP num = PROTECT(Rf_allocVector(REALSXP, 1));
    REAL(num)[0] = 42;
    extptr.set_tag(num);

    SEXP tag = extptr.tag();
    expect_true(REAL(tag)[0] == 42);

    UNPROTECT(1);
  }
}
