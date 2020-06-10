#include <testthat.h>
#include <iostream>
#include "cpp11/external_pointer.hpp"

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
    bool deleted = false;
    auto deleter = [&](int* ptr) {
      deleted = true;
      delete ptr;
    };

    cpp11::external_pointer<int, decltype(deleter)> uniq(new int, deleter);
    expect_true(deleted == false);
    uniq.reset();
    expect_true(deleted == true);
  }
}
