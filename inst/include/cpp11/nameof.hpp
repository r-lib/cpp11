/// Distributed under the Boost Software License, Version 1.0. (See
/// http://www.boost.org/LICENSE_1_0.txt)

#include <array>
#include <string>
#include <tuple>
#include <utility>

namespace cpp11 {
namespace detail {

#ifdef _MSC_VER
#define ARROW_PRETTY_FUNCTION __FUNCSIG__
#else
#define ARROW_PRETTY_FUNCTION __PRETTY_FUNCTION__
#endif

template <typename T>
const char* raw() {
  return ARROW_PRETTY_FUNCTION;
}

template <typename T>
size_t raw_sizeof() {
  return sizeof(ARROW_PRETTY_FUNCTION);
}

#undef ARROW_PRETTY_FUNCTION

constexpr bool starts_with(char const* haystack, char const* needle) {
  return needle[0] == '\0' ||
         (haystack[0] == needle[0] && starts_with(haystack + 1, needle + 1));
}

constexpr size_t search(char const* haystack, char const* needle) {
  return haystack[0] == '\0' || starts_with(haystack, needle)
             ? 0
             : search(haystack + 1, needle) + 1;
}

const size_t typename_prefix = search(raw<double>(), "double");

template <typename T>
size_t struct_class_prefix() {
#ifdef _MSC_VER
  return starts_with(raw<T>() + typename_prefix, "struct ")
             ? 7
             : starts_with(raw<T>() + typename_prefix, "class ") ? 6 : 0;
#else
  return 0;
#endif
}

template <typename T>
size_t typename_length() {
  // raw_sizeof<T>() - raw_sizeof<double>() ==
  //     (length of T's name) - strlen("double")
  // (length of T's name) ==
  //     raw_sizeof<T>() - raw_sizeof<double>() + strlen("double")
  return raw_sizeof<T>() - struct_class_prefix<T>() - raw_sizeof<double>() + 6;
}

template <typename T>
const char* typename_begin() {
  return raw<T>() + struct_class_prefix<T>() + typename_prefix;
}

}  // namespace detail

template <typename T>
std::string nameof(bool strip_namespace = false) {
  std::string name{detail::typename_begin<T>(), detail::typename_length<T>()};
  if (strip_namespace) {
    auto i = name.find_last_of("::");
    if (i != std::string::npos) {
      name = name.substr(i + 1);
    }
  }
  return name;
}

}  // namespace cpp11
