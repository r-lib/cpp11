#include "cpp11/integers.hpp"
#include "cpp11/list.hpp"
#include "cpp11/strings.hpp"

[[cpp11::register]] SEXP data_frame_() {
  using namespace cpp11::literals;
  cpp11::writable::list out({
      "nums"_nm = {1, 2, 3},
      "letters"_nm = {"x", "y", "z"},
  });

  out.attr("class") = "data.frame";
  out.attr("row.names") = {NA_INTEGER, -3};

  return out;
}
