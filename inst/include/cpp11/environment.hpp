#include "cpp11/as.hpp"    // for sexp
#include "cpp11/sexp.hpp"  // for sexp

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
  proxy operator[](SEXP name) { return {env_, name}; }
  proxy operator[](const char* name) { return operator[](safe[Rf_install](name)); }

  bool exists(SEXP name) {
    SEXP res = safe[Rf_findVarInFrame3](env_, name, FALSE);
    return res != R_UnboundValue;
  }
  bool exists(const char* name) { return exists(safe[Rf_install](name)); }

  void remove(SEXP name) { R_removeVarFromFrame(name, env_); }

  void remove(const char* name) { remove(safe[Rf_install](name)); }
};

}  // namespace cpp11
