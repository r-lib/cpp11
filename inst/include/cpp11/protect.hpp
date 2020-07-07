#pragma once

#include "cpp11/R.hpp"  // for SEXP, SEXPREC, CDR, R_NilValue, CAR, R_Pres...

#include <csetjmp>        // for longjmp, setjmp, jmp_buf
#include <exception>      // for exception
#include <string>         // for string, basic_string
#include "R_ext/Error.h"  // for Rf_error, Rf_warning
#include "R_ext/Print.h"  // for REprintf
#include "R_ext/Utils.h"  // for R_CheckUserInterrupt
#include "Rversion.h"     // for R_VERSION, R_Version

#if defined(R_VERSION) && R_VERSION >= R_Version(3, 5, 0)
#define HAS_UNWIND_PROTECT
#endif

namespace cpp11 {
class unwind_exception : public std::exception {
 public:
  SEXP token;
  unwind_exception(SEXP token_) : token(token_) {}
};

static SEXP preserve(SEXP obj) {
  PROTECT(obj);
  R_PreserveObject(obj);
  UNPROTECT(1);
  return obj;
}

static SEXP protect_list = preserve(Rf_cons(R_NilValue, R_NilValue));

inline SEXP protect_sexp(SEXP obj) {
  if (obj == R_NilValue) {
    return R_NilValue;
  }
#ifdef CPP11_USE_PRESERVE_OBJECT
  R_PreserveObject(obj);
  return obj;
#endif
  PROTECT(obj);

  // Add a new cell that points to the previous end.
  SEXP cell = PROTECT(Rf_cons(protect_list, CDR(protect_list)));
  SET_TAG(cell, obj);

  SETCDR(protect_list, cell);
  if (CDR(cell) != R_NilValue) {
    SETCAR(CDR(cell), cell);
  }

  UNPROTECT(2);

  return cell;
}

inline void print_protect() {
  SEXP head = protect_list;
  while (head != R_NilValue) {
    REprintf("%x CAR: %x CDR: %x TAG: %x\n", head, CAR(head), CDR(head), TAG(head));
    head = CDR(head);
  }
  REprintf("---\n");
}

inline void release_existing_protections() {
#if !defined(HAS_UNWIND_PROTECT) && !defined(CPP11_USE_PRESERVE_OBJECT)
  SEXP first = CDR(protect_list);
  if (first != R_NilValue) {
    SETCAR(first, R_NilValue);
    SETCDR(protect_list, R_NilValue);
  }
#endif
}

inline void release_protect(SEXP protect) {
  if (protect == R_NilValue) {
    return;
  }
#ifdef CPP11_USE_PRESERVE_OBJECT
  R_ReleaseObject(protect);
  return;
#endif

  SEXP before = CAR(protect);
  SEXP after = CDR(protect);

  if (before == R_NilValue && after == R_NilValue) {
    Rf_error("should never happen");
  }

  SETCDR(before, after);
  if (after != R_NilValue) {
    SETCAR(after, before);
  }
}

#ifdef HAS_UNWIND_PROTECT

namespace internal {
struct unwind_data_t {
  std::jmp_buf jmpbuf;
};

// We need to first jump back into the C++ stacks because you can't safely throw
// exceptions from C stack frames.
inline void maybe_jump(void* unwind_data, Rboolean jump) {
  if (jump) {
    unwind_data_t* data = static_cast<unwind_data_t*>(unwind_data);
    longjmp(data->jmpbuf, 1);
  }
}

template <typename Fun>
inline SEXP unwind_protect_unwrap_sexp(void* data) {
  Fun* callback = (Fun*)data;
  return (*callback)();
}

template <typename Fun>
SEXP unwind_protect_unwrap_void(void* data) {
  Fun* callback = (Fun*)data;
  (*callback)();
  return R_NilValue;
}

}  // namespace internal

inline SEXP init_unwind_continuation() {
  SEXP res = R_MakeUnwindCont();
  R_PreserveObject(res);
  return res;
}

/// Unwind Protection from C longjmp's, like those used in R error
/// handling
/// @param Fun A lamdba function
/// @param code The code to which needs to be protected
template <typename Fun>
SEXP unwind_protect_sexp(Fun code) {
  static SEXP token = init_unwind_continuation();
  internal::unwind_data_t unwind_data;

  if (setjmp(unwind_data.jmpbuf)) {
    throw unwind_exception(token);
  }
  SEXP res = R_UnwindProtect(&internal::unwind_protect_unwrap_sexp<Fun>, &code,
                             internal::maybe_jump, &unwind_data, token);

  return res;
}

template <typename Fun>
void unwind_protect(Fun code) {
  static SEXP token = init_unwind_continuation();
  internal::unwind_data_t unwind_data;

  if (setjmp(unwind_data.jmpbuf)) {
    throw unwind_exception(token);
  }

  R_UnwindProtect(&internal::unwind_protect_unwrap_void<Fun>, &code, internal::maybe_jump,
                  &unwind_data, token);
}
#else
// Don't do anything if we don't have unwind protect. This will leak C++ resources,
// including those held by cpp11 objects, but the other alternatives are also not great.
template <typename Fun>
SEXP unwind_protect_sexp(Fun code) {
  return code();
}

template <typename Fun>
void unwind_protect(Fun code) {
  code();
}
#endif

struct protect {
  template <typename F>
  struct function;
  template <typename R, typename... A>
  struct function<R(A...)> {
    constexpr R operator()(A... a) const {
      return unwind_protect_sexp([&] { return ptr_(a...); });
    }
    R (*ptr_)(A...);
  };
  template <typename R, typename... A>
  constexpr function<R(A...)> operator[](R (&raw)(A...)) const {
    return {&raw};
  }
};
constexpr struct protect safe = {};

inline void check_user_interrupt() {
  unwind_protect([&] { R_CheckUserInterrupt(); });
}

template <typename... Args>
void stop(const char* fmt, Args... args) {
  unwind_protect([&] { Rf_error(fmt, args...); });
}

template <typename... Args>
void stop(const std::string& fmt, Args... args) {
  unwind_protect([&] { Rf_error(fmt.c_str(), args...); });
}

template <typename... Args>
void warning(const char* fmt, Args... args) {
  unwind_protect([&] { Rf_warning(fmt, args...); });
}

template <typename... Args>
void warning(const std::string& fmt, Args... args) {
  unwind_protect([&] { Rf_warning(fmt.c_str(), args...); });
}

}  // namespace cpp11
