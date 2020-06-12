#include "cpp11/as.hpp"
#include "cpp11/sexp.hpp"  // for sexp

#include "Rversion.h"

#if R_VERSION >= R_Version(4, 0, 0)
#define HAS_REMOVE_VAR_FROM_FRAME
#endif

#ifndef HAS_REMOVE_VAR_FROM_FRAME
#include "cpp11/function.hpp"
#endif

namespace cpp11 {

class environment {
 private:
  sexp env_;

  class proxy {
    SEXP parent_;
    SEXP name_;

   public:
    proxy(SEXP parent, SEXP name) : parent_(parent), name_(name) {}

    template <typename T>
    proxy& operator=(T value) {
      unwind_protect([&] { Rf_defineVar(name_, as_sexp(value), parent_); });
      return *this;
    }
    operator SEXP() const { return safe[Rf_findVarInFrame3](parent_, name_, TRUE); };
    operator sexp() const { return SEXP(); };
  };

 public:
  environment(SEXP env) : env_(env) {}
  proxy operator[](SEXP name) const { return {env_, name}; }
  proxy operator[](const char* name) const { return operator[](safe[Rf_install](name)); }

  bool exists(SEXP name) const {
    SEXP res = safe[Rf_findVarInFrame3](env_, name, FALSE);
    return res != R_UnboundValue;
  }
  bool exists(const char* name) const { return exists(safe[Rf_install](name)); }

  void remove(SEXP name) {
#ifdef HAS_REMOVE_VAR_FROM_FRAME
    R_removeVarFromFrame(name, env_);
#else
    auto remove = package("base")["remove"];
    remove(name, "envir"_nm = env_);
#endif
  }

  void remove(const char* name) { remove(safe[Rf_install](name)); }

  R_xlen_t size() const { return Rf_xlength(env_); }
};

}  // namespace cpp11
