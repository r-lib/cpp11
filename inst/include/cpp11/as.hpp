#pragma once

#include <cmath>             // for modf
#include <initializer_list>  // for initializer_list
#include <memory>            // for std::shared_ptr, std::weak_ptr, std::unique_ptr
#include <string>            // for string, basic_string
#include <type_traits>       // for decay, enable_if, is_same, is_convertible

#include "cpp11/R.hpp"        // for SEXP, SEXPREC, Rf_xlength, R_xlen_t
#include "cpp11/protect.hpp"  // for stop, protect, safe, protect::function

namespace cpp11 {

template <typename T>
using decay_t = typename std::decay<T>::type;

template <bool C, typename R = void>
using enable_if_t = typename std::enable_if<C, R>::type;

template <typename T>
struct is_smart_ptr : std::false_type {};

template <typename T>
struct is_smart_ptr<std::shared_ptr<T>> : std::true_type {};

template <typename T>
struct is_smart_ptr<std::unique_ptr<T>> : std::true_type {};

template <typename T>
struct is_smart_ptr<std::weak_ptr<T>> : std::true_type {};

template <typename T>
using is_constructible_from_sexp = std::integral_constant<
    bool, std::is_same<T, SEXP>::value ||
              (!is_smart_ptr<T>::value &&  // workaround for gcc 4.8
               std::is_class<T>::value && std::is_constructible<T, SEXP>::value)>;

template <typename T>
using is_convertible_to_sexp = std::is_convertible<T, SEXP>;

template <typename T, typename Enable = void>
struct as_cpp_impl;

/// If T defines explicit construction from SEXP, that will override as_cpp_impl
template <typename T>
enable_if_t<is_constructible_from_sexp<T>::value, T> as_cpp(SEXP from) {
  static_assert(std::is_same<decay_t<T>, T>::value, "");
  return T(from);
}

template <typename T, typename = enable_if_t<!is_constructible_from_sexp<T>::value>>
auto as_cpp(SEXP from) -> decltype(as_cpp_impl<T>::convert(from)) {
  static_assert(std::is_same<decay_t<T>, T>::value, "");
  return as_cpp_impl<T>::convert(from);
}

/// Temporary workaround for compatibility with cpp11 0.1.0
template <typename T>
enable_if_t<!std::is_same<decay_t<T>, T>::value, decay_t<T>> as_cpp(SEXP from) {
  return as_cpp<decay_t<T>>(from);
}

template <typename T, typename Enable = void>
struct as_sexp_impl;

/// If T defines explicit construction from SEXP, that will override as_sexp_impl
template <typename T>
enable_if_t<is_convertible_to_sexp<T>::value, SEXP> as_sexp(const T& from) {
  return static_cast<SEXP>(from);
}

/// Override as_sexp so that as_sexp(r_string(...)) results in a single element vector
/// instead of a CHRSXP
class r_string;
inline SEXP as_sexp(r_string from);

template <typename T, typename = enable_if_t<!is_convertible_to_sexp<T>::value>>
auto as_sexp(const T& from) -> decltype(as_sexp_impl<decay_t<T>>::convert(from)) {
  return as_sexp_impl<decay_t<T>>::convert(from);
}

template <typename T>
using is_integral = std::integral_constant<bool, std::is_integral<T>::value &&
                                                     !std::is_same<T, bool>::value &&
                                                     !std::is_same<T, char>::value>;

template <typename T, typename R = void>
using enable_if_integral = enable_if_t<is_integral<T>::value, R>;

template <typename T, typename R = void>
using enable_if_floating_point =
    typename std::enable_if<std::is_floating_point<T>::value, R>::type;

template <typename E, typename R = void>
using enable_if_enum = enable_if_t<std::is_enum<E>::value, R>;

template <typename T, typename R = void>
using enable_if_is_sexp = enable_if_t<std::is_same<T, SEXP>::value, R>;

template <typename T, typename R = void>
using enable_if_convertible_to_sexp = enable_if_t<std::is_convertible<T, SEXP>::value, R>;

template <typename T, typename R = void>
using disable_if_convertible_to_sexp =
    enable_if_t<!std::is_convertible<T, SEXP>::value, R>;

namespace detail {

// https://stackoverflow.com/a/1521682/2055486
static bool is_convertible_without_loss_to_integer(double value) {
  double int_part;
  return std::modf(value, &int_part) == 0.0;
}

template <typename E, typename Underlying = typename std::underlying_type<E>::type>
using enum_to_int_type =
    typename std::conditional<std::is_same<char, Underlying>::value,
                              int,  // `char` triggers undesired string conversions
                              Underlying>::type;

}  // namespace detail

template <typename T>
struct as_cpp_impl<T, enable_if_integral<T>> {
  static T convert(SEXP from) {
    if (Rf_isInteger(from)) {
      if (Rf_xlength(from) == 1) {
        return INTEGER_ELT(from, 0);
      }
    } else if (Rf_isReal(from)) {
      if (Rf_xlength(from) == 1) {
        if (ISNA(REAL_ELT(from, 0))) {
          return NA_INTEGER;
        }
        double value = REAL_ELT(from, 0);
        if (detail::is_convertible_without_loss_to_integer(value)) {
          return value;
        }
      }
    } else if (Rf_isLogical(from)) {
      if (Rf_xlength(from) == 1) {
        if (LOGICAL_ELT(from, 0) == NA_LOGICAL) {
          return NA_INTEGER;
        }
      }
    }

    stop("Expected single integer value");
  }
};

template <typename T>
struct as_sexp_impl<T, enable_if_integral<T>> {
  static SEXP convert(T from) { return safe[Rf_ScalarInteger](from); }
};

template <typename E>
struct as_cpp_impl<E, enable_if_enum<E>> {
  static E convert(SEXP from) {
    if (Rf_isInteger(from)) {
      return static_cast<E>(as_cpp<detail::enum_to_int_type<E>>(from));
    }

    stop("Expected single integer value");
  }
};

template <typename E>
struct as_sexp_impl<E, enable_if_enum<E>> {
  static SEXP convert(E from) {
    return as_sexp(static_cast<detail::enum_to_int_type<E>>(from));
  }
};

template <>
struct as_cpp_impl<bool> {
  static bool convert(SEXP from) {
    if (Rf_isLogical(from)) {
      if (Rf_xlength(from) == 1) {
        return LOGICAL_ELT(from, 0) == 1;
      }
    }

    stop("Expected single logical value");
  }
};

template <>
struct as_sexp_impl<bool> {
  static SEXP convert(bool from) { return safe[Rf_ScalarLogical](from); }
};

template <typename T>
struct as_cpp_impl<T, enable_if_floating_point<T>> {
  static T convert(SEXP from) {
    if (Rf_isReal(from)) {
      if (Rf_xlength(from) == 1) {
        return REAL_ELT(from, 0);
      }
    }
    // All 32 bit integers can be coerced to doubles, so we just convert them.
    if (Rf_isInteger(from)) {
      if (Rf_xlength(from) == 1) {
        if (INTEGER_ELT(from, 0) == NA_INTEGER) {
          return NA_REAL;
        }
        return INTEGER_ELT(from, 0);
      }
    }

    // Also allow NA values
    if (Rf_isLogical(from)) {
      if (Rf_xlength(from) == 1) {
        if (LOGICAL_ELT(from, 0) == NA_LOGICAL) {
          return NA_REAL;
        }
      }
    }

    stop("Expected single double value");
  }
};

template <typename T>
struct as_sexp_impl<T, enable_if_floating_point<T>> {
  static SEXP convert(T from) { return safe[Rf_ScalarReal](from); }
};

template <>
struct as_cpp_impl<const char*> {
  static const char* convert(SEXP from) {
    if (Rf_isString(from)) {
      if (Rf_xlength(from) == 1) {
        // NB: vmaxget/vmaxset here would cause translated strings to be freed before
        // return. Without this explicit management, the return value of as_cpp<const
        // char*>(str) will freed at the end of the call to .C, .Call, or .External
        return unwind_protect([&] { return Rf_translateCharUTF8(STRING_ELT(from, 0)); });
      }
    }

    stop("Expected string vector of length 1");
  }
};

template <>
struct as_sexp_impl<const char*> {
  static SEXP convert(const char* from) {
    return unwind_protect([&] { return Rf_ScalarString(Rf_mkCharCE(from, CE_UTF8)); });
  }
};

template <>
struct as_sexp_impl<char*> {
  static SEXP convert(const char* from) { return as_sexp(from); }
};

template <>
struct as_cpp_impl<std::string> {
  static std::string convert(SEXP from) { return as_cpp<const char*>(from); }
};

template <>
struct as_sexp_impl<std::string> {
  static SEXP convert(const std::string& from) { return as_sexp(from.c_str()); }
};

template <>
struct as_cpp_impl<char> {
  static char convert(SEXP from) { return as_cpp<const char*>(from)[0]; }
};

template <>
struct as_sexp_impl<char> {
  static SEXP convert(char from) { return as_sexp(std::string({from})); }
};

namespace detail {

template <SEXPTYPE t>
using sexptype_constant = std::integral_constant<SEXPTYPE, t>;

inline int* get_raws(SEXP vec, sexptype_constant<LGLSXP>) { return LOGICAL(vec); }
inline int* get_raws(SEXP vec, sexptype_constant<INTSXP>) { return INTEGER(vec); }
inline double* get_raws(SEXP vec, sexptype_constant<REALSXP>) { return REAL(vec); }

template <typename Container, SEXPTYPE t>
SEXP as_sexp_raws(const Container& from, sexptype_constant<t> sexptype) {
  R_xlen_t size = from.size();
  SEXP data = PROTECT(safe[Rf_allocVector](sexptype, size));

  auto raw_data = get_raws(data, sexptype);
  for (auto el : from) {
    *raw_data++ = el;
  }

  UNPROTECT(1);
  return data;
}

template <typename Container, SEXPTYPE t>
Container as_cpp_raws(SEXP from, sexptype_constant<t> sexptype) {
  // FIXME altrep is broken
  auto raw_data = get_raws(from, sexptype);
  return Container{raw_data, raw_data + Rf_xlength(from)};
}

template <typename Container, typename ToCstring>
SEXP as_sexp_strings(const Container& from, const ToCstring& to_c_str) {
  R_xlen_t size = from.size();
  SEXP data = PROTECT(safe[Rf_allocVector](STRSXP, size));

  try {
    R_xlen_t i = 0;
    for (const auto& s : from) {
      SET_STRING_ELT(data, i++, safe[Rf_mkCharCE](to_c_str(s), CE_UTF8));
    }
  } catch (const unwind_exception& e) {
    UNPROTECT(1);
    throw e;
  }

  UNPROTECT(1);
  return data;
}

template <typename Container>
Container as_cpp_strings(SEXP from) {
  struct iterator {
    using difference_type = int;
    using value_type = const char*;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::forward_iterator_tag;

    const char* operator*() const {
      return Rf_translateCharUTF8(STRING_ELT(data_, index_));
    }

    iterator& operator++() {
      ++index_;
      return *this;
    }

    bool operator!=(const iterator& other) const { return index_ != other.index_; }

    SEXP data_;
    R_xlen_t index_;
  };

  iterator begin{from, 0};
  iterator end{from, Rf_xlength(from)};
  return Container(begin, end);
}

}  // namespace detail

template <typename Container>
struct as_cpp_impl<Container,
                   enable_if_t<is_integral<typename Container::value_type>::value>> {
  static Container convert(SEXP from) {
    return detail::as_cpp_raws<Container>(from, detail::sexptype_constant<INTSXP>{});
  }
};

template <typename Container>
struct as_cpp_impl<
    Container,
    enable_if_t<std::is_floating_point<typename Container::value_type>::value>> {
  static Container convert(SEXP from) {
    return detail::as_cpp_raws<Container>(from, detail::sexptype_constant<REALSXP>{});
  }
};

template <typename Container>
struct as_cpp_impl<
    Container, enable_if_t<std::is_same<typename Container::value_type, bool>::value>> {
  static Container convert(SEXP from) {
    return detail::as_cpp_raws<Container>(from, detail::sexptype_constant<LGLSXP>{});
  }
};

template <typename Container>
struct as_cpp_impl<Container, enable_if_t<std::is_constructible<
                                  typename Container::value_type, const char*>::value>> {
  static Container convert(SEXP from) { return detail::as_cpp_strings<Container>(from); }
};

template <typename Container>
struct as_sexp_impl<Container,
                    enable_if_t<is_integral<typename Container::value_type>::value>> {
  static SEXP convert(const Container& from) {
    return detail::as_sexp_raws<Container>(from, detail::sexptype_constant<INTSXP>{});
  }
};

template <typename Container>
struct as_sexp_impl<
    Container,
    enable_if_t<std::is_floating_point<typename Container::value_type>::value>> {
  static SEXP convert(const Container& from) {
    return detail::as_sexp_raws<Container>(from, detail::sexptype_constant<REALSXP>{});
  }
};

template <typename Container>
struct as_sexp_impl<
    Container, enable_if_t<std::is_same<typename Container::value_type, bool>::value>> {
  static SEXP convert(const Container& from) {
    return detail::as_sexp_raws<Container>(from, detail::sexptype_constant<LGLSXP>{});
  }
};

template <typename Container>
struct as_sexp_impl<
    Container,
    enable_if_t<std::is_same<typename Container::value_type, std::string>::value>> {
  static SEXP convert(const Container& from) {
    return detail::as_sexp_strings<Container>(
        from, [](const std::string& s) { return s.c_str(); });
  }
};

template <typename Container>
struct as_sexp_impl<Container, enable_if_t<std::is_convertible<
                                   typename Container::value_type, const char*>::value>> {
  static SEXP convert(const Container& from) {
    return detail::as_sexp_strings<Container>(
        from, [](const typename Container::value_type& s) {
          return static_cast<const char*>(s);
        });
  }
};

inline SEXP as_sexp(std::initializer_list<int> from) {
  return as_sexp<std::initializer_list<int>>(from);
}

inline SEXP as_sexp(std::initializer_list<double> from) {
  return as_sexp<std::initializer_list<double>>(from);
}

inline SEXP as_sexp(std::initializer_list<bool> from) {
  return as_sexp<std::initializer_list<bool>>(from);
}

inline SEXP as_sexp(std::initializer_list<const char*> from) {
  return as_sexp<std::initializer_list<const char*>>(from);
}

}  // namespace cpp11
