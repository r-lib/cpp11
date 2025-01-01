#pragma once

#include <map>
#include <unordered_map>
#include "cpp11/R.hpp"
#include "cpp11/protect.hpp"
#include "cpp11/list.hpp"
#include "cpp11/strings.hpp"

namespace cpp11 {

template <typename Key, typename Value>
SEXP map_to_sexp(const std::map<Key, Value>& map) {
  cpp11::writable::list result(map.size());
  cpp11::writable::strings names(map.size());

  size_t i = 0;
  for (const auto& pair : map) {
    result[i] = cpp11::as_sexp(pair.second);
    names[i] = cpp11::as_sexp(pair.first);
    ++i;
  }

  result.names() = names;
  return result;
}

template <typename Key, typename Value>
SEXP unordered_map_to_sexp(const std::unordered_map<Key, Value>& map) {
  cpp11::writable::list result(map.size());
  cpp11::writable::strings names(map.size());

  size_t i = 0;
  for (const auto& pair : map) {
    result[i] = cpp11::as_sexp(pair.second);
    names[i] = cpp11::as_sexp(pair.first);
    ++i;
  }

  result.names() = names;
  return result;
}

}  // namespace cpp11
