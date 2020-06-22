#pragma once

#include <stddef.h>          // for ptrdiff_t
#include <array>             // for array
#include <cstdio>            // for snprintf, size_t
#include <exception>         // for exception
#include <initializer_list>  // for initializer_list
#include <iosfwd>            // for string
#include <iterator>          // for forward_iterator_tag
#include <stdexcept>         // for out_of_range
#include <string>            // for basic_string
#include <type_traits>       // for is_same, enable_if, is_constructible
#include "cpp11/R.hpp"       // for SEXP, SEXPREC, R_xlen_t, Rf_xlength
#include "cpp11/as.hpp"      // for as_sexp, is_vector_of_strings
#include "cpp11/attribute_proxy.hpp"
#include "cpp11/named_arg.hpp"
#include "cpp11/protect.hpp"  // for protect, safe, protect::function
#include "cpp11/string.hpp"   // for string

namespace cpp11 {

class type_error : public std::exception {
 public:
  type_error(int expected, int actual) : expected_(expected), actual_(actual), str_("") {}
  virtual const char* what() const noexcept {
    snprintf(str_, 64, "Invalid input type, expected '%s' actual '%s'",
             Rf_type2char(expected_), Rf_type2char(actual_));
    return str_;
  }

 private:
  int expected_;
  int actual_;
  mutable char str_[64];
};

// Forward Declarations
class named_arg;

namespace writable {
template <typename T>
class vector;
}  // namespace writable

// Declarations
template <typename T>
class vector {
 public:
  vector() = default;

  vector(const SEXP data);

  vector(const SEXP data, bool is_altrep);

#ifdef LONG_VECTOR_SUPPORT
  T operator[](const int pos) const;
#endif
  T operator[](const R_xlen_t pos) const;
  T operator[](const string& name) const;

  T at(const R_xlen_t pos) const;

  bool contains(const string& name) const;

  vector& operator=(const vector& rhs) = default;

  bool is_altrep() const;

  R_xlen_t size() const;

  operator SEXP() const;

  operator sexp() const;

  /// Provide access to the underlying data, mainly for interface
  /// compatibility with std::vector
  SEXP data() const;

  sexp attr(const char* name) const {
    return SEXP(attribute_proxy<vector<T>>(*this, name));
  }

  sexp attr(const std::string& name) const {
    return SEXP(attribute_proxy<vector<T>>(*this, name.c_str()));
  }

  sexp attr(SEXP name) const { return SEXP(attribute_proxy<vector<T>>(*this, name)); }

  vector<string> names() const {
    SEXP nms = SEXP(attribute_proxy<vector<T>>(*this, R_NamesSymbol));
    if (nms == R_NilValue) {
      return vector<string>();
    }

    return nms;
  }

  class const_iterator {
   public:
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;

    const_iterator(const vector* data, R_xlen_t pos);

    inline const_iterator& operator+(R_xlen_t pos);
    inline ptrdiff_t operator-(const const_iterator& other) const;

    inline const_iterator& operator++();
    inline const_iterator& operator--();

    inline const_iterator& operator+=(R_xlen_t pos);
    inline const_iterator& operator-=(R_xlen_t pos);

    inline bool operator!=(const const_iterator& other) const;
    inline bool operator==(const const_iterator& other) const;

    inline T operator*();

    friend class writable::vector<T>::iterator;

   private:
    const vector* data_;
    void fill_buf(R_xlen_t pos);

    R_xlen_t pos_;
    std::array<T, 64 * 64> buf_;
    R_xlen_t block_start_ = 0;
    R_xlen_t length_ = 0;
  };

 public:
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;

  const_iterator begin() const;
  const_iterator end() const;

  const_iterator cbegin() const;
  const_iterator cend() const;

 private:
  SEXP data_ = R_NilValue;
  bool is_altrep_ = false;
  T* data_p_ = nullptr;
  R_xlen_t length_ = 0;

  static T* get_p(bool is_altrep, SEXP data);

  static SEXP valid_type(SEXP data);

  friend class writable::vector<T>;
};

namespace writable {

template <typename T>
using has_begin_fun = std::decay<decltype(*begin(std::declval<T>()))>;

/// Double vectors, read write access to new or copied vectors
template <typename T>
class vector : public cpp11::vector<T> {
 private:
  SEXP protect_ = R_NilValue;

  // These are necessary because type names are not directly accessible in
  // template inheritance
  using cpp11::vector<T>::data_;
  using cpp11::vector<T>::data_p_;
  using cpp11::vector<T>::is_altrep_;
  using cpp11::vector<T>::length_;

  R_xlen_t capacity_ = 0;

 public:
  class proxy {
   private:
    const SEXP data_;
    const R_xlen_t index_;
    T* const p_;
    bool is_altrep_;

   public:
    proxy(SEXP data, const R_xlen_t index, T* const p, bool is_altrep);

    proxy& operator=(T rhs);

    operator T() const;
  };

  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef proxy value_type;
  typedef proxy* pointer;
  typedef proxy& reference;

  class iterator : public cpp11::vector<T>::const_iterator {
   private:
    const vector& data_;
    using cpp11::vector<T>::const_iterator::block_start_;
    using cpp11::vector<T>::const_iterator::pos_;
    using cpp11::vector<T>::const_iterator::buf_;
    using cpp11::vector<T>::const_iterator::length_;
    using cpp11::vector<T>::const_iterator::fill_buf;

   public:
    using difference_type = ptrdiff_t;
    using value_type = proxy;
    using pointer = proxy*;
    using reference = proxy&;
    using iterator_category = std::forward_iterator_tag;

    iterator(const vector& data, R_xlen_t pos);

    inline iterator& operator++();

    inline proxy operator*();

    using cpp11::vector<T>::const_iterator::operator!=;

    inline iterator& operator+(R_xlen_t rhs);
  };

  vector() = default;
  vector(const SEXP& data);
  vector(SEXP&& data);
  vector(const SEXP& data, bool is_altrep);
  vector(SEXP&& data, bool is_altrep);
  vector(std::initializer_list<T> il);
  vector(std::initializer_list<named_arg> il);
  vector(std::initializer_list<const char*> il);

  template <typename Iter>
  vector(Iter first, Iter last);

  template <typename V, typename W = has_begin_fun<V>>
  vector(const V& obj);

  vector(const R_xlen_t size);

  ~vector();

  vector(const vector& rhs);
  vector(vector&& rhs);

  vector(const cpp11::vector<T>& rhs);

  vector& operator=(const vector& rhs);
  vector& operator=(vector&& rhs);

#ifdef LONG_VECTOR_SUPPORT
  proxy operator[](const int pos) const;
#endif
  proxy operator[](const R_xlen_t pos) const;
  proxy operator[](const string& name) const;

  void push_back(T value);
  void push_back(const named_arg& value);
  void pop_back();

  void resize(R_xlen_t count);

  void reserve(R_xlen_t new_capacity);

  iterator insert(R_xlen_t pos, T value);
  iterator erase(R_xlen_t pos);

  void clear();

  iterator begin() const;
  iterator end() const;

  using cpp11::vector<T>::cbegin;
  using cpp11::vector<T>::cend;

  attribute_proxy<vector<T>> attr(const char* name) const {
    return attribute_proxy<vector<T>>(*this, name);
  }

  attribute_proxy<vector<T>> attr(const std::string& name) const {
    return attribute_proxy<vector<T>>(*this, name.c_str());
  }

  attribute_proxy<vector<T>> attr(SEXP name) const {
    return attribute_proxy<vector<T>>(*this, name);
  }

  attribute_proxy<vector<T>> names() const {
    return attribute_proxy<vector<T>>(*this, R_NamesSymbol);
  }

  operator SEXP() const;
};
}  // namespace writable

// Implementations below

template <typename T>
inline vector<T>::vector(const SEXP data)
    : data_(valid_type(data)),
      is_altrep_(ALTREP(data)),
      data_p_(get_p(ALTREP(data), data)),
      length_(Rf_xlength(data)) {}

template <typename T>
inline vector<T>::vector(const SEXP data, bool is_altrep)
    : data_(valid_type(data)),
      is_altrep_(is_altrep),
      data_p_(get_p(is_altrep, data)),
      length_(Rf_xlength(data)) {}

template <typename T>
inline bool vector<T>::is_altrep() const {
  return is_altrep_;
}

template <typename T>
inline R_xlen_t vector<T>::size() const {
  return length_;
}

template <typename T>
inline vector<T>::operator SEXP() const {
  return data_;
}

template <typename T>
inline vector<T>::operator sexp() const {
  return data_;
}

/// Provide access to the underlying data, mainly for interface
/// compatibility with std::vector
template <typename T>
inline SEXP vector<T>::data() const {
  return data_;
}

template <typename T>
inline typename vector<T>::const_iterator vector<T>::begin() const {
  return const_iterator(this, 0);
}

template <typename T>
inline typename vector<T>::const_iterator vector<T>::end() const {
  return const_iterator(this, length_);
}

template <typename T>
inline typename vector<T>::const_iterator vector<T>::cbegin() const {
  return const_iterator(this, 0);
}

template <typename T>
inline typename vector<T>::const_iterator vector<T>::cend() const {
  return const_iterator(this, length_);
}

template <typename T>
vector<T>::const_iterator::const_iterator(const vector* data, R_xlen_t pos)
    : data_(data), pos_(pos), buf_() {
  if (data_->is_altrep()) {
    fill_buf(pos);
  }
}

template <typename T>
inline typename vector<T>::const_iterator& vector<T>::const_iterator::operator++() {
  ++pos_;
  if (data_->is_altrep() && pos_ >= block_start_ + length_) {
    fill_buf(pos_);
  }
  return *this;
}

template <typename T>
inline typename vector<T>::const_iterator& vector<T>::const_iterator::operator--() {
  --pos_;
  if (data_->is_altrep() && pos_ > 0 && pos_ < block_start_) {
    fill_buf(std::max(static_cast<R_xlen_t>(0), pos_ - 64));
  }
  return *this;
}

template <typename T>
inline typename vector<T>::const_iterator& vector<T>::const_iterator::operator+=(
    R_xlen_t i) {
  pos_ += i;
  if (data_->is_altrep() && pos_ >= block_start_ + length_) {
    fill_buf(pos_);
  }
  return *this;
}

template <typename T>
inline typename vector<T>::const_iterator& vector<T>::const_iterator::operator-=(
    R_xlen_t i) {
  pos_ -= i;
  if (data_->is_altrep() && pos_ >= block_start_ + length_) {
    fill_buf(std::max(static_cast<R_xlen_t>(0), pos_ - 64));
  }
  return *this;
}

template <typename T>
inline bool vector<T>::const_iterator::operator!=(
    const vector<T>::const_iterator& other) const {
  return pos_ != other.pos_;
}

template <typename T>
inline bool vector<T>::const_iterator::operator==(
    const vector<T>::const_iterator& other) const {
  return pos_ == other.pos_;
}

template <typename T>
inline ptrdiff_t vector<T>::const_iterator::operator-(
    const vector<T>::const_iterator& other) const {
  return pos_ - other.pos_;
}

template <typename T>
inline typename vector<T>::const_iterator& vector<T>::const_iterator::operator+(
    R_xlen_t rhs) {
  pos_ += rhs;
  if (data_->is_altrep() && pos_ >= block_start_ + length_) {
    fill_buf(pos_);
  }
  return *this;
}

template <typename T>
inline T cpp11::vector<T>::operator[](const string& name) const {
  SEXP names = this->names();
  R_xlen_t size = Rf_xlength(names);

  for (R_xlen_t pos = 0; pos < size; ++pos) {
    auto cur = Rf_translateCharUTF8(STRING_ELT(names, pos));
    if (name == cur) {
      return operator[](pos);
    }
  }

  throw std::out_of_range("vector");
}

template <typename T>
inline bool cpp11::vector<T>::contains(const string& name) const {
  SEXP names = this->names();
  R_xlen_t size = Rf_xlength(names);

  for (R_xlen_t pos = 0; pos < size; ++pos) {
    auto cur = Rf_translateCharUTF8(STRING_ELT(names, pos));
    if (name == cur) {
      return true;
    }
  }

  return false;
}

template <typename T>
inline T vector<T>::const_iterator::operator*() {
  if (data_->is_altrep()) {
    return buf_[pos_ - block_start_];
  } else {
    return data_->data_p_[pos_];
  }
}

#ifdef LONG_VECTOR_SUPPORT
template <typename T>
inline T vector<T>::operator[](const int pos) const {
  return operator[](static_cast<R_xlen_t>(pos));
}
#endif

namespace writable {

template <typename T>
vector<T>::proxy::proxy(SEXP data, const R_xlen_t index, T* const p, bool is_altrep)
    : data_(data), index_(index), p_(p), is_altrep_(is_altrep) {}

template <typename T>
inline typename vector<T>::proxy vector<T>::iterator::operator*() {
  if (data_.is_altrep()) {
    return proxy(data_.data(), pos_, &buf_[pos_ - block_start_], true);
  } else {
    return proxy(data_.data(), pos_,
                 data_.data_p_ != nullptr ? &data_.data_p_[pos_] : nullptr, false);
  }
}

template <typename T>
vector<T>::iterator::iterator(const vector& data, R_xlen_t pos)
    : vector<T>::const_iterator(&data, pos), data_(data) {}

template <typename T>
inline typename vector<T>::iterator& vector<T>::iterator::operator++() {
  ++pos_;
  if (data_.is_altrep() && pos_ >= block_start_ + length_) {
    fill_buf(pos_);
  }
  return *this;
}

template <typename T>
inline typename vector<T>::iterator& vector<T>::iterator::operator+(R_xlen_t rhs) {
  pos_ += rhs;
  if (data_.is_altrep() && pos_ >= block_start_ + length_) {
    fill_buf(pos_);
  }
  return *this;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::begin() const {
  return iterator(*this, 0);
}

template <typename T>
inline typename vector<T>::iterator vector<T>::end() const {
  return iterator(*this, length_);
}

template <typename T>
inline vector<T>::vector(const SEXP& data)
    : cpp11::vector<T>(safe[Rf_shallow_duplicate](data)),
      protect_(protect_sexp(data_)),
      capacity_(length_) {}

template <typename T>
inline vector<T>::vector(const SEXP& data, bool is_altrep)
    : cpp11::vector<T>(safe[Rf_shallow_duplicate](data), is_altrep),
      protect_(protect_sexp(data_)),
      capacity_(length_) {}

template <typename T>
inline vector<T>::vector(SEXP&& data)
    : cpp11::vector<T>(data), protect_(protect_sexp(data_)), capacity_(length_) {}

template <typename T>
inline vector<T>::vector(SEXP&& data, bool is_altrep)
    : cpp11::vector<T>(data, is_altrep),
      protect_(protect_sexp(data_)),
      capacity_(length_) {}

template <typename T>
template <typename Iter>
inline vector<T>::vector(Iter first, Iter last) : vector() {
  reserve(last - first);
  while (first != last) {
    push_back(*first);
    ++first;
  }
}

template <typename T>
template <typename V, typename W>
inline vector<T>::vector(const V& obj) : vector() {
  auto first = obj.begin();
  auto last = obj.end();
  reserve(last - first);
  while (first != last) {
    push_back(*first);
    ++first;
  }
}

template <typename T>
inline vector<T>::vector(R_xlen_t size) : vector() {
  resize(size);
}

template <typename T>
inline vector<T>::~vector() {
  release_protect(protect_);
}

#ifdef LONG_VECTOR_SUPPORT
template <typename T>
inline typename vector<T>::proxy vector<T>::operator[](const int pos) const {
  return operator[](static_cast<R_xlen_t>(pos));
}
#endif

template <typename T>
inline typename vector<T>::proxy vector<T>::operator[](const R_xlen_t pos) const {
  if (is_altrep_) {
    return {data_, pos, nullptr, true};
  }
  return {data_, pos, &data_p_[pos], false};
}

template <typename T>
inline typename vector<T>::proxy vector<T>::operator[](const string& name) const {
  SEXP names = this->names();
  R_xlen_t size = Rf_xlength(names);

  for (R_xlen_t pos = 0; pos < size; ++pos) {
    auto cur = Rf_translateCharUTF8(STRING_ELT(names, pos));
    if (name == cur) {
      return operator[](pos);
    }
  }

  throw std::out_of_range("vector");
}

template <typename T>
inline vector<T>::vector(const vector<T>& rhs)
    : cpp11::vector<T>(safe[Rf_shallow_duplicate](rhs.data_)),
      protect_(protect_sexp(data_)),
      capacity_(rhs.capacity_) {}

template <typename T>
inline vector<T>::vector(vector<T>&& rhs)
    : cpp11::vector<T>(rhs.data_),
      protect_(protect_sexp(data_)),
      capacity_(rhs.capacity_) {
  rhs.data_ = R_NilValue;
  rhs.protect_ = R_NilValue;
}

template <typename T>
inline vector<T>::vector(const cpp11::vector<T>& rhs)
    : cpp11::vector<T>(safe[Rf_shallow_duplicate](rhs.data_)),
      protect_(protect_sexp(data_)),
      capacity_(rhs.length_) {}

// We don't release the old object until the end in case we throw an exception
// during the duplicate.
template <typename T>
inline vector<T>& vector<T>::operator=(const vector<T>& rhs) {
  if (data_ == rhs.data_) {
    return *this;
  }

  cpp11::vector<T>::operator=(rhs);

  auto old_protect = protect_;

  data_ = safe[Rf_shallow_duplicate](rhs.data_);
  protect_ = protect_sexp(data_);

  release_protect(old_protect);

  capacity_ = rhs.capacity_;

  return *this;
}

template <typename T>
inline vector<T>& vector<T>::operator=(vector<T>&& rhs) {
  if (data_ == rhs.data_) {
    return *this;
  }

  cpp11::vector<T>::operator=(rhs);

  SEXP old_protect = protect_;

  data_ = rhs.data_;
  protect_ = protect_sexp(data_);

  release_protect(old_protect);

  capacity_ = rhs.capacity_;

  rhs.data_ = R_NilValue;
  rhs.protect_ = R_NilValue;

  return *this;
}

template <typename T>
inline void vector<T>::pop_back() {
  --length_;
}

template <typename T>
inline void vector<T>::resize(R_xlen_t count) {
  reserve(count);
  length_ = count;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::insert(R_xlen_t pos, T value) {
  push_back(value);

  R_xlen_t i = length_ - 1;
  while (i > pos) {
    operator[](i) = (T) operator[](i - 1);
    --i;
  };
  operator[](pos) = value;

  return begin() + pos;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::erase(R_xlen_t pos) {
  R_xlen_t i = pos;
  while (i < length_ - 1) {
    operator[](i) = (T) operator[](i + 1);
    ++i;
  }
  pop_back();

  return begin() + pos;
}

template <typename T>
inline void vector<T>::clear() {
  length_ = 0;
}

template <typename T>
inline vector<T>::operator SEXP() const {
  if (length_ < capacity_) {
    SETLENGTH(data_, length_);
  }
  return data_;
}

}  // namespace writable

// TODO: is there a better condition we could use, e.g. assert something true
// rather than three things false?
template <typename C, typename T>
using is_container_but_not_sexp_or_string = typename std::enable_if<
    !std::is_constructible<C, SEXP>::value &&
        !std::is_same<typename std::decay<C>::type, std::string>::value &&
        !std::is_same<typename std::decay<T>::type, std::string>::value,
    typename std::decay<C>::type>::type;

template <typename C, typename T = typename std::decay<C>::type::value_type>
// typename T = typename C::value_type>
is_container_but_not_sexp_or_string<C, T> as_cpp(SEXP from) {
  auto obj = cpp11::vector<T>(from);
  return {obj.begin(), obj.end()};
}

// TODO: could we make this generalize outside of std::string?
template <typename C, typename T = C>
using is_vector_of_strings = typename std::enable_if<
    std::is_same<typename std::decay<T>::type, std::string>::value,
    typename std::decay<C>::type>::type;

template <typename C, typename T = typename std::decay<C>::type::value_type>
// typename T = typename C::value_type>
is_vector_of_strings<C, T> as_cpp(SEXP from) {
  auto obj = cpp11::vector<cpp11::string>(from);
  typename std::decay<C>::type res;
  auto it = obj.begin();
  while (it != obj.end()) {
    string s = *it;
    res.emplace_back(static_cast<std::string>(s));
    ++it;
  }
  return res;
}

}  // namespace cpp11
