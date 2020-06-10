#include <vector>
#include "Rcpp.h"
#include "cpp11/sexp.hpp"

[[cpp11::export]] void cpp11_release_(int n) {
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

[[cpp11::export]] void rcpp_release_(int n) {
  std::vector<Rcpp::RObject> x;
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
