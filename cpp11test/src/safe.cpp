#include <cstring>
#include "headers/doubles.hpp"
#include "headers/protect.hpp"

[[cpp11::register]] SEXP cpp11_safe_(SEXP x_sxp) {
  SEXP err = R_NilValue;
  const size_t ERROR_SIZE = 2048;
  char buf[ERROR_SIZE] = "";

  try {
    const cpp11::doubles x(x_sxp);
    // Rf_error("R error"); // This will not call dtors
    // throw std::runtime_error("C++ error");
    // cpp11::unwind_protect([&]() { Rf_error("R error"); });
    SEXP out = cpp11::unwind_protect([&] { return Rf_allocVector(REALSXP, 1); });

    return out;
  }

  catch (cpp11::unwind_exception& e) {
    err = e.token;
  } catch (std::exception& e) {
    strncpy(buf, e.what(), ERROR_SIZE - 1);
  }

  if (buf[0] != '\0') {
    Rf_error("%s", buf);
  } else if (err != R_NilValue) {
#ifdef HAS_UNWIND_PROTECT
    R_ContinueUnwind(err);
#endif
  }

  return R_NilValue;
}
