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

  test_that("external_pointer preserves attributes when moved (issue #308)") {
    // Test move constructor
    {
      int* value = new int(42);
      cpp11::external_pointer<int> p(value);
      
      // Set an attribute on the external pointer
      Rf_setAttrib(p, R_ClassSymbol, Rf_mkString("test_class"));
      
      // Verify attribute exists before move
      SEXP class_attr = Rf_getAttrib(p, R_ClassSymbol);
      expect_true(class_attr != R_NilValue);
      
      // Move the external pointer using move constructor
      cpp11::external_pointer<int> p_moved = std::move(p);
      
      // Verify attribute is preserved after move
      SEXP class_attr_after = Rf_getAttrib(p_moved, R_ClassSymbol);
      expect_true(class_attr_after != R_NilValue);
      expect_true(strcmp(CHAR(STRING_ELT(class_attr_after, 0)), "test_class") == 0);
      
      // Clean up
      p_moved.release();
    }
    
    // Test move assignment operator
    {
      int* value1 = new int(1);
      int* value2 = new int(2);
      cpp11::external_pointer<int> p1(value1);
      cpp11::external_pointer<int> p2(value2);
      
      // Set an attribute on p1
      Rf_setAttrib(p1, R_ClassSymbol, Rf_mkString("test_class"));
      
      // Move assign p1 to p2
      p2 = std::move(p1);
      
      // Verify attribute is preserved after move assignment
      SEXP class_attr_after = Rf_getAttrib(p2, R_ClassSymbol);
      expect_true(class_attr_after != R_NilValue);
      expect_true(strcmp(CHAR(STRING_ELT(class_attr_after, 0)), "test_class") == 0);
      
      // Clean up
      p2.release();
    }
  }
}
