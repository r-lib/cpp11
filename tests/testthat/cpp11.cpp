#include "cpp11/declarations.hpp"
using namespace cpp11;
// single_27.cpp
int foo();
extern "C" SEXP _single_27_foo() {
  BEGIN_CPP11
  return cpp11::as_sexp(foo());
  END_CPP11
}
