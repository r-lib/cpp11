#include "cpp11/strings.hpp"
#include <random>
#include <vector>

#include <Rcpp.h>

// Test benchmark for string proxy assignment performance.
// We don't unwind_protect() before each `SET_STRING_ELT()` call,
// as that kills performance.
[[cpp11::register]] cpp11::writable::strings string_proxy_assignment_() {
  R_xlen_t size = 100000;

  cpp11::writable::strings x(size);

  cpp11::r_string elt(NA_STRING);

  for (R_xlen_t i = 0; i < size; ++i) {
    x[i] = elt;
  }

  return x;
}

// Test benchmark for string push back performance.
// We don't unwind_protect() before each `SET_STRING_ELT()` call,
// as that kills performance.
[[cpp11::register]] cpp11::writable::strings string_push_back_() {
  R_xlen_t size = 100000;

  cpp11::writable::strings x;

  cpp11::r_string elt(NA_STRING);

  for (R_xlen_t i = 0; i < size; ++i) {
    x.push_back(elt);
  }

  return x;
}

// issue 406

std::random_device rd;
std::mt19937 gen(rd());

double random_double() {
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(gen);
}

int random_int(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(gen);
}

std::string random_string() {
  std::string s(10, '\0');
  for (size_t i = 0; i < 10; i++) {
    s[i] = random_int(0, 25) + 'a';
  }
  return s;
}

[[cpp11::register]] cpp11::strings grow_strings_cpp11_(size_t n, int seed) {
  gen.seed(seed);
  cpp11::writable::strings x;
  for (size_t i = 0; i < n; ++i) {
    x.push_back(random_string());
  }
  return x;
}

[[cpp11::register]] Rcpp::CharacterVector grow_strings_rcpp_(size_t n, int seed) {
  gen.seed(seed);
  Rcpp::CharacterVector x(n);
  for (size_t i = 0; i < n; ++i) {
    x[i] = random_string();
  }
  return x;
}

[[cpp11::register]] SEXP grow_strings_manual_(size_t n, int seed) {
  gen.seed(seed);
  SEXP data_ = PROTECT(Rf_allocVector(STRSXP, 0));
  size_t size_ = 0;
  size_t capacity_ = 0;
  for (size_t i = 0; i < n; ++i) {
    if (size_ == capacity_) {
      capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
      SEXP new_data_ = PROTECT(Rf_allocVector(STRSXP, capacity_));
      for (size_t j = 0; j < size_; ++j) {
        SET_STRING_ELT(new_data_, j, STRING_ELT(data_, j));
      }
      UNPROTECT(2);
      data_ = PROTECT(new_data_);
    }
    SET_STRING_ELT(data_, size_++, Rf_mkChar(random_string().c_str()));
  }
  // copy back down to size
  if (size_ < capacity_) {
    SEXP new_data_ = PROTECT(Rf_allocVector(STRSXP, size_));
    for (size_t j = 0; j < size_; ++j) {
      SET_STRING_ELT(new_data_, j, STRING_ELT(data_, j));
    }
    UNPROTECT(2);
    return new_data_;
  } else {
    UNPROTECT(1);
    return data_;
  }
}

[[cpp11::register]] cpp11::strings assign_cpp11_(size_t n, int seed) {
  gen.seed(seed);
  cpp11::writable::strings x(n);
  for (size_t i = 0; i < n; ++i) {
    x[i] = random_string();
  }
  return x;
}

[[cpp11::register]] Rcpp::CharacterVector assign_rcpp_(size_t n, int seed) {
  gen.seed(seed);
  Rcpp::CharacterVector x(n);
  for (size_t i = 0; i < n; ++i) {
    x[i] = random_string();
  }
  return x;
}
