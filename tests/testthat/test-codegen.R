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

describe("get_exported_functions", {
  it("returns an empty tibble given a non-existent file", {
    f <- tempfile()
    decorations <- decor::cpp_decorations(files = f, is_attribute = TRUE)
    res <- get_exported_functions(decorations, "cpp11")
    expect_equal(names(res), c("file", "line", "decoration", "params", "context", "name", "return_type", "args"))
    expect_equal(NROW(res), 0)
  })

  it("returns an empty tibble given a empty file", {
    f <- tempfile()
    file.create(f)
    decorations <- decor::cpp_decorations(files = f, is_attribute = TRUE)
    res <- get_exported_functions(decorations, "cpp11")
    expect_equal(names(res), c("file", "line", "decoration", "params", "context", "name", "return_type", "args"))
    expect_equal(NROW(res), 0)
  })

  it("works with a single export", {
    decorations <- decor::cpp_decorations(files = test_path("single.cpp"), is_attribute = TRUE)
    res <- get_exported_functions(decorations, "cpp11")
    expect_equal(names(res), c("file", "line", "decoration", "params", "context", "name", "return_type", "args"))
    expect_equal(NROW(res), 1L)
    expect_equal(res$name, "foo")
    expect_equal(res$return_type, "int")
    expect_equal(names(res$args[[1]]), c("type", "name", "default"))
    expect_equal(NROW(res$args[[1]]), 0)
  })

  it("works with multiple exports", {
    decorations <- decor::cpp_decorations(files = test_path("multiple.cpp"), is_attribute = TRUE)
    res <- get_exported_functions(decorations, "cpp11")
    expect_equal(names(res), c("file", "line", "decoration", "params", "context", "name", "return_type", "args"))
    expect_equal(NROW(res), 3L)
    expect_equal(res$name, c("foo", "bar", "baz"))
    expect_equal(res$return_type, c("int", "double", "bool"))
    expect_equal(names(res$args[[1]]), c("type", "name", "default"))
    expect_equal(NROW(res$args[[1]]), 0)

    expect_equal(names(res$args[[2]]), c("type", "name", "default"))
    expect_equal(NROW(res$args[[2]]), 1)
    expect_equal(res$args[[2]]$type, "bool")
    expect_equal(res$args[[2]]$name, "run")
    expect_equal(res$args[[2]]$default, NA_character_)

    expect_equal(names(res$args[[3]]), c("type", "name", "default"))
    expect_equal(NROW(res$args[[3]]), 2)
    expect_equal(res$args[[3]]$type, c("bool", "int"))
    expect_equal(res$args[[3]]$name, c("run", "value"))
    expect_equal(res$args[[3]]$default, c(NA_character_, "0"))
  })
})
