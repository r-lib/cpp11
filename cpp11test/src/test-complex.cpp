#include "cpp11/complexes.hpp"

#include "cpp11/strings.hpp"

#include <testthat.h>

context("complexes-C++") {
  test_that("complexes::r_vector(SEXP)") {
    cpp11::complexes x(Rf_allocVector(CPLXSXP, 2));
    expect_true(x.size() == 2);

    expect_error(cpp11::complexes(Rf_allocVector(INTSXP, 2)));
  }

  test_that("complexes::r_vector::const_iterator()") {
    cpp11::complexes x(Rf_allocVector(CPLXSXP, 100));
    COMPLEX(x)[0] = Rcomplex{1, 1};
    COMPLEX(x)[1] = Rcomplex{2, 2};
    COMPLEX(x)[2] = Rcomplex{3, 3};
    COMPLEX(x)[3] = Rcomplex{4, 4};
    COMPLEX(x)[4] = Rcomplex{5, 5};
    COMPLEX(x)[97] = Rcomplex{98, 98};
    COMPLEX(x)[98] = Rcomplex{99, 99};
    COMPLEX(x)[99] = Rcomplex{100, 100};
    expect_true(x.size() == 100);

    auto it = x.begin();
    auto it2 = x.begin();
    expect_true(it == it2);

    ++it;
    expect_true(!(it == it2));
    expect_true(it != it2);

    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};
    cpp11::r_complex ninety_nine{99, 99};
    cpp11::r_complex ninety_eight{98, 98};
    cpp11::r_complex one_hundred{100, 100};

    ++it;
    expect_true(*it == three);
    --it;
    expect_true(*it == two);
    --it;

    it += 99;
    expect_true(*it == one_hundred);
    --it;
    expect_true(*it == ninety_nine);
    --it;
    expect_true(*it == ninety_eight);
    it -= 95;
    expect_true(*it == three);
  }

  test_that("complexes.push_back()") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};

    cpp11::writable::complexes x;
    x.push_back(one);
    x.push_back(two);
    x.push_back(three);

    expect_true(x.size() == 3);
    expect_true(x[0] == one);
    expect_true(x[1] == two);
    expect_true(x[2] == three);
  }
  test_that("complexes.resize()") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};

    cpp11::writable::complexes x;
    x.resize(3);
    x[0] = one;
    x[1] = two;
    x[2] = three;

    expect_true(x.size() == 3);
    expect_true(x[0] == one);
    expect_true(x[1] == two);
    expect_true(x[2] == three);
  }
  test_that("complexes.at()") {
    cpp11::writable::complexes x;

    expect_error(x.at(-1));

    expect_error(x.at(0));

    cpp11::r_complex one{1, 1};

    x.push_back(one);
    expect_true(x.at(0) == one);
    expect_error(x.at(1));
  }
  test_that("complexes.pop_back()") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};

    cpp11::writable::complexes x;

    x.push_back(one);
    x.push_back(two);
    x.pop_back();

    expect_true(x.size() == 1);
    expect_true(x[0] == one);

    expect_error(x.at(1));
  }
  test_that("complexes.insert()") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};

    cpp11::writable::complexes x;

    x.insert(0, one);
    x.insert(0, two);
    x.insert(1, three);
    expect_true(x.size() == 3);

    expect_true(x[0] == two);
    expect_true(x[1] == three);
    expect_true(x[2] == one);
  }
  test_that("complexes.erase()") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};
    cpp11::r_complex four{4, 4};
    cpp11::r_complex five{5, 5};

    cpp11::writable::complexes x;

    x.push_back(one);
    x.push_back(two);
    x.push_back(three);
    x.push_back(four);
    x.push_back(five);

    expect_true(x.size() == 5);

    x.erase(0);

    expect_true(x.size() == 4);
    expect_true(x[0] == two);
    expect_true(x[1] == three);
    expect_true(x[2] == four);
    expect_true(x[3] == five);

    x.erase(2);

    expect_true(x.size() == 3);
    expect_true(x[0] == two);
    expect_true(x[1] == three);
    expect_true(x[2] == five);
  }
  test_that("complexes.iterator* = ") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};
    cpp11::r_complex four{4, 4};

    cpp11::writable::complexes x;
    x.push_back(one);
    x.push_back(two);
    x.push_back(three);
    auto it = x.begin() + 1;
    *it = three;
    ++it;
    *it = four;

    expect_true(x.size() == 3);
    expect_true(x[0] == one);
    expect_true(x[1] == three);
    expect_true(x[2] == four);
  }

  test_that("writable::complexes(SEXP)") {
    Rcomplex one{1, 1};
    Rcomplex two{2, 2};
    Rcomplex three{3, 3};
    Rcomplex four{4, 4};
    Rcomplex five{5, 5};
    Rcomplex six{6, 6};
    Rcomplex seven{7, 7};

    SEXP x = PROTECT(Rf_allocVector(CPLXSXP, 5));

    COMPLEX(x)[0] = one;
    COMPLEX(x)[1] = two;
    COMPLEX(x)[2] = three;
    COMPLEX(x)[3] = four;
    COMPLEX(x)[4] = five;

    cpp11::writable::complexes y(x);
    y[0] = cpp11::r_complex(six);

    expect_true(x != y.data());

    expect_true(COMPLEX(x)[0].r == one.r);
    expect_true(COMPLEX(x)[0].i == one.i);
    expect_true(y[0] == cpp11::r_complex(six));

    cpp11::writable::complexes z(y);
    z[0] = cpp11::r_complex(seven);

    expect_true(z.data() != y.data());

    expect_true(COMPLEX(x)[0].r == one.r);
    expect_true(COMPLEX(x)[0].i == one.i);
    expect_true(y[0] == cpp11::r_complex(six));
    expect_true(z[0] == cpp11::r_complex(seven));

    UNPROTECT(1);
  }
  test_that("writable::complexes(SEXP, bool)") {
    Rcomplex five{5, 5};
    SEXP x = PROTECT(Rf_ScalarComplex(five));
    cpp11::writable::complexes y(x, false);

    expect_true(COMPLEX(y)[0].r == five.r);
    expect_true(COMPLEX(y)[0].i == five.i);
    UNPROTECT(1);
  }

  test_that("writable::complexes(SEXP) assignment") {
    cpp11::r_complex zero{0, 0};
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};

    cpp11::writable::complexes x({one, two, three});
    cpp11::writable::complexes y({zero});
    y = x;
    expect_true(y.size() == 3);
    expect_true(y.data() != x.data());
    expect_true(y.is_altrep() == x.is_altrep());
  }

  test_that("writable::complexes(SEXP) move assignment") {
    cpp11::r_complex zero{0, 0};
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};

    cpp11::writable::complexes x({one, two, three});
    cpp11::writable::complexes y({zero});
    auto x_data = x.data();

    y = std::move(x);
    expect_true(y.size() == 3);
    expect_true(y.data() == x_data);
    expect_true(y.is_altrep() == false);
  }

  test_that("complexes::names(empty)") {
    cpp11::complexes x;
    auto nms = x.names();
    expect_true(nms.size() == 0);
  }

  test_that("complexes::names") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};

    using namespace cpp11::literals;
    cpp11::writable::complexes x({"a"_nm = one, "b"_nm = two, "c"_nm = three});
    expect_true(x[0] == one);
    expect_true(x[1] == two);
    expect_true(x[2] == three);

    expect_true(x.contains("a"));
    expect_true(!x.contains("d"));

    expect_true(x["a"] == one);
    expect_true(x["b"] == two);
    expect_true(x["c"] == three);

    cpp11::sexp nms(x.names());
    expect_true(Rf_xlength(nms) == 3);
    auto nms0 = CHAR(STRING_ELT(nms, 0));
    auto nms1 = CHAR(STRING_ELT(nms, 1));
    auto nms2 = CHAR(STRING_ELT(nms, 2));
    expect_true(strcmp(nms0, "a") == 0);
    expect_true(strcmp(nms1, "b") == 0);
    expect_true(strcmp(nms2, "c") == 0);
  }

  test_that("complexes::attr") {
    cpp11::complexes x(PROTECT(Rf_allocVector(CPLXSXP, 2)));
    COMPLEX(x)[0] = Rcomplex{1, 1};
    COMPLEX(x)[1] = Rcomplex{2, 2};

    SEXP foo = Rf_install("foo");
    Rf_setAttrib(x, foo, Rf_mkString("bar"));

    // This doesn't compile by design
    // x.attr("foo") = "bar";

    // But this will
    cpp11::writable::complexes y(x);
    y.attr("foo") = "baz";

    expect_true(strcmp(CHAR(STRING_ELT(x.attr("foo"), 0)), "bar") == 0);
    expect_true(strcmp(CHAR(STRING_ELT(y.attr("foo"), 0)), "baz") == 0);

    UNPROTECT(1);
  }

  test_that("writable::complexes(std::vector<r_complex>::iterator)") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};

    std::vector<cpp11::r_complex> x({one, two});
    cpp11::writable::complexes y(x.begin(), x.end());

    expect_true(y.size() == 2);
    expect_true(y[0] == one);
    expect_true(y[1] == two);
  }

  test_that("writable::complexes(std::vector<r_complex>)") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};

    std::vector<cpp11::r_complex> x({one, two, three});
    cpp11::writable::complexes y(x);

    expect_true(y.size() == 3);
    expect_true(y[0] == one);
    expect_true(y[2] == three);
  }

  test_that("writable::complexes attributes are kept when converted to complexes") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};

    cpp11::writable::complexes x({one, two});
    x.names() = {"a", "b"};
    cpp11::strings x_nms(x.names());
    expect_true(x_nms[0] == "a");
    expect_true(x_nms[1] == "b");

    cpp11::complexes y(x);
    cpp11::strings y_nms(y.names());
    expect_true(y_nms[0] == "a");
    expect_true(y_nms[1] == "b");
  }

  test_that("comparison operator works") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};

    using namespace cpp11;
    cpp11::complexes base({one, two});
    cpp11::complexes same_values({one, two});
    cpp11::complexes diff_length({one});
    cpp11::complexes diff_values({one, three});

    expect_true(base == base);
    expect_true(base == base);
    expect_true(base == same_values);
    expect_true(!(base == diff_length));
    expect_true(!(base == diff_values));

    expect_true(!(base != base));
    expect_true(!(base != same_values));
    expect_true(base != diff_length);
    expect_true(base != diff_values);
  }

  test_that("proxy comparison works symmetrically") {
    cpp11::r_complex x{1, 2};
    cpp11::writable::complexes y({x});

    expect_true(x == y[0]);
    expect_true(y[0] == x);
  }

  test_that("complexes operator[] and at") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};

    cpp11::complexes x(Rf_allocVector(CPLXSXP, 2));
    COMPLEX(x)[0] = Rcomplex(one);
    COMPLEX(x)[1] = Rcomplex(two);

    int i0 = 0;
    R_xlen_t x0 = 0;
    size_t s0 = 0;

    expect_true(x[i0] == one);
    expect_true(x[x0] == one);
    expect_true(x[s0] == one);

    expect_true(x.at(i0) == one);
    expect_true(x.at(x0) == one);
    expect_true(x.at(s0) == one);
  }

  test_that("writable::complexes operator[] and at") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};

    cpp11::writable::complexes x(Rf_allocVector(CPLXSXP, 2));
    COMPLEX(x)[0] = Rcomplex(one);
    COMPLEX(x)[1] = Rcomplex(two);

    int i0 = 0;
    R_xlen_t x0 = 0;
    size_t s0 = 0;

    expect_true(x[i0] == one);
    expect_true(x[x0] == one);
    expect_true(x[s0] == one);

    expect_true(x.at(i0) == one);
    expect_true(x.at(x0) == one);
    expect_true(x.at(s0) == one);
  }

  test_that("operator[] and at with names") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};

    using namespace cpp11::literals;
    cpp11::writable::complexes x({"a"_nm = one, "b"_nm = two});
    cpp11::complexes y(x);

    expect_true(x["a"] == one);
    expect_true(x["b"] == two);
    expect_error(x["c"] == two);

    expect_true(y["a"] == one);
    expect_true(y["b"] == two);
    expect_error(y["c"] == two);
  }

  test_that("complexes::find") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};

    using namespace cpp11::literals;
    cpp11::writable::complexes x({"a"_nm = one, "b"_nm = two});
    cpp11::complexes y(x);

    expect_true(x.find("a") == x.begin());
    expect_true(x.find("b") == x.begin() + 1);
    expect_true(x.find("c") == x.end());

    expect_true(y.find("a") == y.begin());
    expect_true(y.find("b") == y.begin() + 1);
    expect_true(y.find("c") == y.end());
  }

  test_that("writable::complexes compound assignments") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};

    cpp11::writable::complexes x({one});

    auto x0 = x[0];
    expect_true(x0 == one);

    // Arithmetic is not defined on Rcomplex or r_complex,
    // so using it on a proxy also fails and is not defined
    // expect_error(x0 += two);
    // expect_error(x0 -= two);
    // expect_error(x0 *= two);
    // expect_error(x0 /= two);
    // expect_error(x0--);
    // expect_error(x0++);
    // expect_error(++x0);
    // expect_error(--x0);
  }

  test_that("writable::complexes convert to complexes with correct size (#128)") {
    cpp11::r_complex one{1, 1};
    cpp11::r_complex two{2, 2};
    cpp11::r_complex three{3, 3};

    cpp11::writable::complexes foo;
    foo.push_back(one);
    foo.push_back(two);
    foo.push_back(three);

    cpp11::complexes bar(foo);
    expect_true(Rf_xlength(bar) == 3);
  }
}
