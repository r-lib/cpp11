describe("pkg_links_to_rcpp", {
  it("works with single package in LinkingTo", {
    pkg <- local_package()

    expect_false(pkg_links_to_rcpp(pkg_path(pkg)))

    pkg$set("LinkingTo", "Rcpp")
    pkg$write()

    expect_true(pkg_links_to_rcpp(pkg_path(pkg)))
  })

  it("works with multiple packages in LinkingTo", {
    pkg <- local_package()

    expect_false(pkg_links_to_rcpp(pkg_path(pkg)))

    pkg$set("LinkingTo", paste("Rcpp", "cpp11", sep = ","))
    pkg$write()

    expect_true(pkg_links_to_rcpp(pkg_path(pkg)))
  })
})

describe("get_call_entries", {
  it("returns an empty string if there are no R files", {
    pkg <- local_package()
    expect_equal(get_call_entries(pkg_path(pkg)), "")
  })

  it("returns an empty string if there are no .Call calls", {
    pkg <- local_package()
    dir.create(file.path(pkg_path(pkg), "R"))
    writeLines("foo <- function() 1", file.path(pkg_path(pkg), "R", "foo.R"))
    expect_equal(get_call_entries(pkg_path(pkg)), "")
  })

  it("returns an empty string for packages without NAMESPACE files", {
    pkg <- local_package()
    dir.create(file.path(pkg_path(pkg), "R"))
    writeLines('foo <- function() .Call("bar")', file.path(pkg_path(pkg), "R", "foo.R"))
    expect_equal(get_call_entries(pkg_path(pkg)), "")
  })

  it("returns an empty string for packages with .Call entries and NAMESPACE files", {
    pkg <- local_package()
    file.create(file.path(pkg_path(pkg), "NAMESPACE"))
    dir.create(file.path(pkg_path(pkg), "R"))
    writeLines('foo <- function() .Call("bar")', file.path(pkg_path(pkg), "R", "foo.R"))
    expect_equal(
      get_call_entries(pkg_path(pkg)),
      c("/* .Call calls */",
        "extern SEXP bar();",
        "",
        "static const R_CallMethodDef CallEntries[] = {",
        "    {\"bar\", (DL_FUNC) &bar, 0},",
        "    {NULL, NULL, 0}",
        "};"
      )
    )
  })
})

describe("wrap_call", {
  it("works with void functions and no arguments", {
    expect_equal(
      wrap_call("foo", "void", tibble::tibble(type = character(), name = character())),
      "  foo();\n  return R_NilValue;"
    )
  })
  it("works with non-void functions and no arguments", {
    expect_equal(
      wrap_call("foo", "bool", tibble::tibble(type = character(), name = character())),
      "  return cpp11::as_sexp(foo());"
    )
  })
  it("works with void functions and some arguments", {
    expect_equal(
      wrap_call("foo", "void", tibble::tibble(type = c("double", "int"), name = c("x", "y"))),
      "  foo(cpp11::unmove(cpp11::as_cpp<double>(x)), cpp11::unmove(cpp11::as_cpp<int>(y)));\n  return R_NilValue;"
    )
  })
  it("works with non-void functions and some arguments", {
    expect_equal(
      wrap_call("foo", "bool", tibble::tibble(type = c("double", "int"), name = c("x", "y"))),
      "  return cpp11::as_sexp(foo(cpp11::unmove(cpp11::as_cpp<double>(x)), cpp11::unmove(cpp11::as_cpp<int>(y))));"
    )
  })
})
