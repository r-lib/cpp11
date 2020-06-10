#include "cpp11/list.hpp"

namespace cpp11 {

template <typename T>
class list_of : public list {
 public:
  list_of(const list& data) : list(data) {}

#ifdef LONG_VECTOR_SUPPORT
  T operator[](int pos) { return operator[](static_cast<R_xlen_t>(pos)); }
#endif

  T operator[](R_xlen_t pos) { return list::operator[](pos); }

  T operator[](const char* pos) { return list::operator[](pos); }
};

namespace writable {
template <typename T>
class list_of : public writable::list {
 public:
  list_of(const list& data) : writable::list(data) {}

#ifdef LONG_VECTOR_SUPPORT
  T operator[](int pos) { return operator[](static_cast<R_xlen_t>(pos)); }
#endif

  T operator[](R_xlen_t pos) {
    return static_cast<SEXP>(writable::list::operator[](pos));
  }

  T operator[](const char* pos) {
    return static_cast<SEXP>(writable::list::operator[](pos));
  }
};
}  // namespace writable

}  // namespace cpp11
