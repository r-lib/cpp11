#include <cstring>
#include "cpp11/R.hpp"
#include "cpp11/doubles.hpp"
#include "cpp11/function.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/logicals.hpp"
#include "cpp11/sexp.hpp"
#include "cpp11/strings.hpp"

#include <testthat.h>

context("doubles-C++") {
  test_that("doubles::r_vector(SEXP)") {
    cpp11::doubles x(Rf_allocVector(REALSXP, 2));
    expect_true(x.size() == 2);

    expect_error(cpp11::doubles(Rf_allocVector(INTSXP, 2)));
  }

  test_that("doubles::r_vector::const_iterator()") {
    cpp11::doubles x(Rf_allocVector(REALSXP, 100));
    REAL(x)[0] = 1;
    REAL(x)[1] = 2;
    REAL(x)[2] = 3;
    REAL(x)[3] = 4;
    REAL(x)[4] = 5;
    REAL(x)[97] = 98;
    REAL(x)[98] = 99;
    REAL(x)[99] = 100;
    expect_true(x.size() == 100);

    auto it = x.begin();
    auto it2 = x.begin();
    expect_true(it == it2);

    ++it;
    expect_true(!(it == it2));
    expect_true(it != it2);

    ++it;
    expect_true(*it == 3);
    --it;
    expect_true(*it == 2);
    --it;

    it += 99;
    expect_true(*it == 100);
    --it;
    expect_true(*it == 99);
    --it;
    expect_true(*it == 98);
    it -= 95;
    expect_true(*it == 3);
  }

  test_that("doubles.push_back()") {
    cpp11::writable::doubles x;
    x.push_back(1);
    x.push_back(2);

    expect_true(x.size() == 2);
    expect_true(x[0] == 1);
    expect_true(x[1] == 2);
  }
  test_that("doubles.resize()") {
    cpp11::writable::doubles x;
    x.resize(2);
    x[0] = 1;
    x[1] = 2;

    expect_true(x.size() == 2);
    expect_true(x[0] == 1);
    expect_true(x[1] == 2);
  }
  test_that("doubles.at()") {
    cpp11::writable::doubles x;

    expect_error(x.at(-1));

    expect_error(x.at(0));

    x.push_back(1);
    expect_true(x.at(0) == 1);
    expect_error(x.at(1));
  }
  test_that("doubles.pop_back()") {
    cpp11::writable::doubles x;

    x.push_back(1);
    x.push_back(2);
    x.pop_back();

    expect_true(x.size() == 1);
    expect_true(x[0] == 1);

    expect_error(x.at(1));
  }
  test_that("doubles.insert()") {
    cpp11::writable::doubles x;

    x.insert(0, 1);
    x.insert(0, 2);
    x.insert(1, 3);
    expect_true(x.size() == 3);

    expect_true(x[0] == 2);
    expect_true(x[1] == 3);
    expect_true(x[2] == 1);
  }
  test_that("doubles.erase()") {
    cpp11::writable::doubles x;

    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);

    expect_true(x.size() == 5);

    x.erase(0);

    expect_true(x.size() == 4);
    expect_true(x[0] == 2);
    expect_true(x[1] == 3);
    expect_true(x[2] == 4);
    expect_true(x[3] == 5);

    x.erase(2);

    expect_true(x.size() == 3);
    expect_true(x[0] == 2);
    expect_true(x[1] == 3);
    expect_true(x[2] == 5);
  }
  test_that("doubles.iterator* = ") {
    cpp11::writable::doubles x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    auto it = x.begin() + 1;
    *it = 3;
    ++it;
    *it = 4;

    expect_true(x.size() == 3);
    expect_true(x[0] == 1);
    expect_true(x[1] == 3);
    expect_true(x[2] == 4);
  }

  test_that("writable::doubles(SEXP)") {
    SEXP x = PROTECT(Rf_allocVector(REALSXP, 5));

    REAL(x)[0] = 1;
    REAL(x)[1] = 2;
    REAL(x)[2] = 3;
    REAL(x)[3] = 4;
    REAL(x)[4] = 5;

    cpp11::writable::doubles y(x);
    y[0] = -1;

    expect_true(x != y.data());

    expect_true(REAL(x)[0] == 1);
    expect_true(y[0] == -1);

    cpp11::writable::doubles z(y);
    z[0] = -2;

    expect_true(z.data() != y.data());

    expect_true(REAL(x)[0] == 1);
    expect_true(y[0] == -1);
    expect_true(z[0] == -2);

    UNPROTECT(1);
  }

  test_that("writable::doubles(initializer_list<named_arg>)") {
    using namespace cpp11::literals;

    SEXP x1 = PROTECT(Rf_allocVector(REALSXP, 1));
    SEXP x2 = PROTECT(Rf_allocVector(REALSXP, 1));
    SEXP x3 = PROTECT(Rf_allocVector(REALSXP, 1));

    SET_REAL_ELT(x1, 0, 0.0);
    SET_REAL_ELT(x2, 0, 5.5);
    SET_REAL_ELT(x3, 0, NA_REAL);

    // From scalar double vectors
    cpp11::writable::doubles x({"one"_nm = x1, "two"_nm = x2, "three"_nm = x3});
    expect_true(x.named());
    expect_true(x["one"] == 0.0);
    expect_true(x["two"] == 5.5);
    expect_true(R_IsNA(x["three"]));

    // From doubles
    cpp11::writable::doubles y({"one"_nm = 0.0, "two"_nm = 5.5, "three"_nm = NA_REAL});
    expect_true(y.named());
    expect_true(y["one"] == 0.0);
    expect_true(y["two"] == 5.5);
    expect_true(R_IsNA(y["three"]));

    UNPROTECT(3);
  }

  test_that("writable::doubles(initializer_list<named_arg>) type check") {
    using namespace cpp11::literals;
    expect_error_as(cpp11::writable::doubles({"one"_nm = true}), cpp11::type_error);
    expect_error_as(cpp11::writable::doubles({"one"_nm = R_NilValue}), cpp11::type_error);
  }

  test_that("writable::doubles(initializer_list<named_arg>) length check") {
    using namespace cpp11::literals;
    SEXP x = PROTECT(Rf_allocVector(REALSXP, 2));
    expect_error_as(cpp11::writable::doubles({"x"_nm = x}), std::length_error);
    UNPROTECT(1);
  }

  test_that("writable::doubles(initializer_list<double>)") {
    cpp11::writable::doubles x({1, 2.5, 3});
    expect_true(x[0] == 1.0);
    expect_true(x[1] == 2.5);
    expect_true(x[2] == 3.0);
  }

  test_that("writable::doubles(SEXP, bool)") {
    SEXP x = PROTECT(Rf_ScalarReal(5.));
    cpp11::writable::doubles y(x, false);

    expect_true(REAL(y)[0] == 5.);
    UNPROTECT(1);
  }

#if defined(__APPLE__)
  test_that("writable::doubles(ALTREP_SEXP)") {
    // ALTREP compact-seq
    auto seq = cpp11::package("base")["seq"];
    cpp11::sexp range = seq(cpp11::as_sexp(1), cpp11::as_sexp(5));

    SEXP x = PROTECT(Rf_coerceVector(range, REALSXP));
    expect_true(ALTREP(x));
    // Need to find (or create) an altrep class that implements duplicate.

    cpp11::writable::doubles y(x);
    y[0] = -1;

    expect_true(x != y.data());

    expect_true(REAL_ELT(x, 0) == 1);
    expect_true(y[0] == -1);

    cpp11::writable::doubles z(y);
    z[0] = -2;

    expect_true(z.data() != y.data());

    expect_true(REAL_ELT(x, 0) == 1);
    expect_true(y[0] == -1);
    expect_true(z[0] == -2);

    z.push_back(6);
    expect_true(z[5] == 6);

    UNPROTECT(1);
  }

  test_that("writable::doubles(SEXP) assignment") {
    cpp11::writable::doubles x({1., 2., 3.});
    cpp11::writable::doubles y({0.});
    y = x;
    expect_true(y.size() == 3);
    expect_true(y.data() != x.data());
    expect_true(y.is_altrep() == x.is_altrep());

    // ALTREP compact-seq
    auto seq = cpp11::package("base")["seq"];
    cpp11::sexp range = seq(cpp11::as_sexp(1), cpp11::as_sexp(5));

    cpp11::writable::doubles z(Rf_coerceVector(range, REALSXP));
    cpp11::writable::doubles w({0.});
    w = z;
    expect_true(w.size() == 5);
    expect_true(w.data() != z.data());
    // Shallow duplication of objects of a very small size (like 1:5) don't result in
    // a new ALTREP object. Make sure we check ALTREP-ness of the newly duplicated object,
    // instead of just blindly inheriting the ALTREP-ness of the thing we duplicate.
    expect_true(w.is_altrep() != z.is_altrep());
    expect_true(w.is_altrep() == ALTREP(w.data()));
  }

  test_that("writable::doubles(SEXP) move assignment") {
    cpp11::writable::doubles x({1., 2., 3.});
    cpp11::writable::doubles y({0.});
    auto x_data = x.data();

    y = std::move(x);
    expect_true(y.size() == 3);
    expect_true(y.data() == x_data);
    expect_true(y.is_altrep() == false);

    // ALTREP compact-seq
    auto seq = cpp11::package("base")["seq"];
    cpp11::sexp range = seq(cpp11::as_sexp(1), cpp11::as_sexp(5));

    cpp11::writable::doubles z(Rf_coerceVector(range, REALSXP));
    cpp11::writable::doubles w({0.});
    expect_true(z.is_altrep() == true);

    auto z_data = z.data();
    w = std::move(z);
    expect_true(w.size() == 5);
    expect_true(w.data() == z_data);
    expect_true(w.is_altrep() == true);
  }

#endif

  test_that("doubles::names(empty)") {
    cpp11::doubles x;
    auto nms = x.names();
    expect_true(nms.size() == 0);
  }

  test_that("doubles::names") {
    using namespace cpp11::literals;
    cpp11::writable::doubles x({"a"_nm = 1., "b"_nm = 2.});
    expect_true(x[0] == 1.);
    expect_true(x[1] == 2.);

    expect_true(x.contains("a"));
    expect_true(!x.contains("c"));

    expect_true(x["a"] == 1.);
    expect_true(x["b"] == 2.);

    cpp11::sexp nms(x.names());
    expect_true(Rf_xlength(nms) == 2);
    auto nms0 = CHAR(STRING_ELT(nms, 0));
    auto nms1 = CHAR(STRING_ELT(nms, 1));
    expect_true(strcmp(nms0, "a") == 0);
    expect_true(strcmp(nms1, "b") == 0);
  }

  test_that("doubles::attr") {
    cpp11::doubles x(PROTECT(Rf_allocVector(REALSXP, 2)));
    REAL(x)[0] = 1;
    REAL(x)[1] = 2;

    SEXP foo = Rf_install("foo");
    Rf_setAttrib(x, foo, Rf_mkString("bar"));

    // This doesn't compile by design
    // x.attr("foo") = "bar";

    // But this will
    cpp11::writable::doubles y(x);
    y.attr("foo") = "baz";

    expect_true(strcmp(CHAR(STRING_ELT(x.attr("foo"), 0)), "bar") == 0);
    expect_true(strcmp(CHAR(STRING_ELT(y.attr("foo"), 0)), "baz") == 0);

    UNPROTECT(1);
  }

  test_that("writable::doubles(std::vector::iterator)") {
    std::vector<double> x({1, 2, 3, 4, 5});
    cpp11::writable::doubles y(x.begin(), x.end());
    expect_true(y.size() == 5);
    expect_true(y[0] == 1);
    expect_true(y[4] == 5);
  }

  test_that("writable::doubles(std::vector)") {
    std::vector<double> x({1, 2, 3, 4, 5});
    cpp11::writable::doubles y(x);
    expect_true(y.size() == 5);
    expect_true(y[0] == 1);
    expect_true(y[4] == 5);
  }

  test_that("writable::doubles attributes are kept when converted to doubles") {
    cpp11::writable::doubles x({1, 2});
    x.names() = {"a", "b"};
    cpp11::strings x_nms(x.names());
    expect_true(x_nms[0] == "a");
    expect_true(x_nms[1] == "b");

    cpp11::doubles y(x);
    cpp11::strings y_nms(y.names());
    expect_true(y_nms[0] == "a");
    expect_true(y_nms[1] == "b");
  }

  test_that("comparison operator works") {
    using namespace cpp11;
    cpp11::doubles base(Rf_allocVector(REALSXP, 2));
    cpp11::doubles same_values(Rf_allocVector(REALSXP, 2));
    cpp11::doubles diff_length(Rf_allocVector(REALSXP, 1));
    cpp11::doubles diff_values(Rf_allocVector(REALSXP, 2));

    REAL(base)[0] = 1;
    REAL(base)[1] = 2;

    REAL(same_values)[0] = 1;
    REAL(same_values)[1] = 2;

    REAL(diff_length)[0] = 1;

    REAL(diff_values)[0] = 1;
    REAL(diff_values)[1] = 3;

    expect_true(base == base);
    expect_true(base == same_values);
    expect_true(!(base == diff_length));
    expect_true(!(base == diff_values));

    expect_true(!(base != base));
    expect_true(!(base != same_values));
    expect_true(base != diff_length);
    expect_true(base != diff_values);
  }
  test_that("is_na(double)") {
    double x = 0.;
    expect_true(!cpp11::is_na(x));

    double y = NA_REAL;
    expect_true(cpp11::is_na(y));
  }

  test_that("as_doubles(integers)") {
    cpp11::writable::integers y;
    y.push_back(10);
    y.push_back(13616);
    y.push_back(124);
    y.push_back(899);
    cpp11::doubles i(cpp11::as_doubles(y));

    expect_true(i[0] == 10);
    expect_true(i[1] == 13616);
    expect_true(i[2] == 124);
    expect_true(i[3] == 899);
    expect_true(cpp11::detail::r_typeof(i) == REALSXP);

    cpp11::writable::strings e;
    e.push_back("a");
    e.push_back("b");
    expect_error(cpp11::as_doubles(e));

    cpp11::writable::integers na{NA_INTEGER, 42};
    cpp11::doubles na2(cpp11::as_doubles(na));
    expect_true(cpp11::is_na(na2[0]));
    expect_true(!cpp11::is_na(na2[1]));
  }

  test_that("as_doubles(logicals)") {
    cpp11::writable::logicals y;

    for (int i = 0; i < 4; i++) {
      y.push_back(i % 2 == 0);
    }

    cpp11::doubles i(cpp11::as_doubles(y));

    expect_true(i[0] == 1.0);
    expect_true(i[1] == 0.0);
    expect_true(i[2] == 1.0);
    expect_true(i[3] == 0.0);
    expect_true(cpp11::detail::r_typeof(i) == REALSXP);
  }

  test_that("doubles operator[] and at") {
    cpp11::doubles x(Rf_allocVector(REALSXP, 2));
    REAL(x)[0] = 1;
    REAL(x)[1] = 2;

    int i0 = 0;
    R_xlen_t x0 = 0;
    size_t s0 = 0;

    expect_true(x[i0] == 1);
    expect_true(x[x0] == 1);
    expect_true(x[s0] == 1);

    expect_true(x.at(i0) == 1);
    expect_true(x.at(x0) == 1);
    expect_true(x.at(s0) == 1);
  }

  test_that("writable::doubles operator[] and at") {
    cpp11::writable::doubles x(Rf_allocVector(REALSXP, 2));
    REAL(x)[0] = 1;
    REAL(x)[1] = 2;

    int i0 = 0;
    R_xlen_t x0 = 0;
    size_t s0 = 0;

    expect_true(x[i0] == 1);
    expect_true(x[x0] == 1);
    expect_true(x[s0] == 1);

    expect_true(x.at(i0) == 1);
    expect_true(x.at(x0) == 1);
    expect_true(x.at(s0) == 1);
  }

  test_that("operator[] and at with names") {
    using namespace cpp11::literals;
    cpp11::writable::doubles x({"a"_nm = 1., "b"_nm = 2.});
    cpp11::doubles y(x);

    expect_true(x["a"] == 1.);
    expect_true(x["b"] == 2.);
    expect_error(x["c"]);

    expect_true(x.at("a") == 1.);
    expect_true(x.at("b") == 2.);
    expect_error(x.at("c"));

    expect_true(y["a"] == 1.);
    expect_true(y["b"] == 2.);
    expect_error(y["c"]);

    expect_true(y.at("a") == 1.);
    expect_true(y.at("b") == 2.);
    expect_error(y.at("c"));
  }

  test_that("doubles::find") {
    using namespace cpp11::literals;
    cpp11::writable::doubles x({"a"_nm = 1., "b"_nm = 2.});
    cpp11::doubles y(x);

    expect_true(x.find("a") == x.begin());
    expect_true(x.find("b") == x.begin() + 1);
    expect_true(x.find("c") == x.end());

    expect_true(y.find("a") == y.begin());
    expect_true(y.find("b") == y.begin() + 1);
    expect_true(y.find("c") == y.end());
  }

  test_that("writable::doubles compound assignments") {
    cpp11::writable::doubles x(Rf_allocVector(REALSXP, 1));
    REAL(x)[0] = 1;

    auto x0 = x[0];
    expect_true(x0 == 1);

    x0 += 3;
    expect_true(x0 == 4);

    x0 -= 2;
    expect_true(x0 == 2);

    x0 *= 2;
    expect_true(x0 == 4);

    x0 /= 2;
    expect_true(x0 == 2);

    x0--;
    expect_true(x0 == 1);

    x0++;
    expect_true(x0 == 2);

    ++x0;
    expect_true(x0 == 3);

    --x0;
    expect_true(x0 == 2);
  }
  test_that("writable::doubles convert to doubles with correct size (#128)") {
    cpp11::writable::doubles foo;
    foo.push_back(1.);
    foo.push_back(2.);
    foo.push_back(3.);

    cpp11::doubles bar(foo);
    expect_true(Rf_xlength(bar) == 3);
  }
}
