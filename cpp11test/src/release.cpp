#include <vector>
#include "headers/sexp.hpp"

#include "Rcpp.h"

[[cpp11::register]] void cpp11_release_(int n) {
  std::vector<cpp11::sexp> x;
  int count = 0;
  while (count < n) {
    x.push_back(Rf_ScalarInteger(count));
    ++count;
  }
  count = 0;
  while (count < n) {
    x.pop_back();
    ++count;
  }
}

[[cpp11::register]] void rcpp_release_(int n) {
#ifdef CPP11_BENCH
  std::vector<Rcpp::RObject> x;
  int count = 0;
  while (count < n) {
    x.push_back(Rcpp::RObject(Rf_ScalarInteger(count)));
    ++count;
  }
  count = 0;
  while (count < n) {
    x.pop_back();
    ++count;
  }
#endif
}
