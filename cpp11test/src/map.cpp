#include "cpp11/as.hpp"
#include "cpp11/doubles.hpp"

[[cpp11::register]] SEXP ordered_map_to_list_(cpp11::doubles x) {
  std::map<double, int> counts;
  int n = x.size();
  for (int i = 0; i < n; i++) {
    counts[x[i]]++;
  }
  return cpp11::as_sexp(counts);
}

[[cpp11::register]] SEXP unordered_map_to_list_(cpp11::doubles x) {
  std::unordered_map<double, int> counts;
  int n = x.size();
  for (int i = 0; i < n; i++) {
    counts[x[i]]++;
  }
  return cpp11::as_sexp(counts);
}
