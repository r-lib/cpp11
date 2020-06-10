#include <cstddef>
#include <memory>
#include "cpp11/sexp.hpp"
#include "cpp11/vector.hpp"

namespace cpp11 {

template <typename T, typename Deleter = std::default_delete<T>>

class external_pointer {
 private:
  sexp data_ = R_NilValue;
  Deleter deleter_;

  static SEXP valid_type(SEXP data) {
    if (TYPEOF(data) != EXTPTRSXP) {
      throw type_error(EXTPTRSXP, TYPEOF(data));
    }

    return data;
  }

 public:
  using pointer = T*;
  using deleter_type = Deleter;

  external_pointer() noexcept {}
  external_pointer(std::nullptr_t) noexcept {}

  external_pointer(SEXP data) : data_(valid_type(data)) {}

  external_pointer(pointer p, deleter_type d)
      : data_(safe[R_MakeExternalPtr]((void*)p, R_NilValue, R_NilValue)), deleter_(d) {}

  ~external_pointer() {
    pointer ptr = get();
    if (ptr == nullptr) {
      return;
    }
    get_deleter()(ptr);
  }

  external_pointer(T* p)
      : data_(safe[R_MakeExternalPtr]((void*)p, R_NilValue, R_NilValue)) {}

  external_pointer& operator=(external_pointer&& r) noexcept {
    reset(r.release());
    deleter_ = std::forward<Deleter>(r.get_deleter());
  }
  template <class U, class E>
  external_pointer& operator=(external_pointer<U, E>&& r) noexcept {
    reset(r.release());
    deleter_ = std::forward<E>(r.get_deleter());
  }
  external_pointer& operator=(std::nullptr_t) noexcept { reset(); };

  operator SEXP() const noexcept { return data_; }

  T* get() const noexcept {
    T* addr = static_cast<T*>(R_ExternalPtrAddr(data_));
    if (addr == nullptr) {
      return nullptr;
    }
    return static_cast<T*>(addr);
  }

  operator T*() noexcept { return get(); }

  T* operator->() const noexcept { return get(); }

  deleter_type get_deleter() const noexcept { return deleter_; }

  pointer release() noexcept {
    if (get() == nullptr) {
      return nullptr;
    }
    T* ptr = get();
    R_ClearExternalPtr(data_);

    return ptr;
  }

  void reset(pointer ptr = pointer()) {
    pointer old_ptr = get();
    data_ = safe[R_MakeExternalPtr]((void*)ptr, R_NilValue, R_NilValue);
    if (old_ptr != nullptr) {
      get_deleter()(old_ptr);
    }
  }

  void swap(external_pointer& other) noexcept {
    SEXP tmp = other.data_;
    other.data_ = data_;
    data_ = tmp;
  }

  operator bool() noexcept { return data_ != nullptr; }
};

template <class T, class Deleter>
void swap(external_pointer<T, Deleter>& lhs, external_pointer<T, Deleter>& rhs) noexcept {
  lhs.swap(rhs);
}

template <class T1, class D1, class T2, class D2>
bool operator==(const external_pointer<T1, D1>& x, const external_pointer<T2, D2>& y) {
  return x.data_ == y.data_;
}

template <class T1, class D1, class T2, class D2>
bool operator!=(const external_pointer<T1, D1>& x, const external_pointer<T2, D2>& y) {
  return x.data_ != y.data_;
}

template <class T1, class D1, class T2, class D2>
bool operator<(const external_pointer<T1, D1>& x, const external_pointer<T2, D2>& y) {
  return x.data_ < y.data_;
}

template <class T1, class D1, class T2, class D2>
bool operator<=(const external_pointer<T1, D1>& x, const external_pointer<T2, D2>& y) {
  return x.data_ <= y.data_;
}

template <class T1, class D1, class T2, class D2>
bool operator>(const external_pointer<T1, D1>& x, const external_pointer<T2, D2>& y) {
  return x.data_ > y.data_;
}

template <class T1, class D1, class T2, class D2>
bool operator>=(const external_pointer<T1, D1>& x, const external_pointer<T2, D2>& y) {
  return x.data_ >= y.data_;
}

}  // namespace cpp11
