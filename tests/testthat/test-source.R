test_that("cpp_source works with the `code` parameter", {
  skip_on_os("solaris")
  dll_info <- cpp_source(
    code = '
    #include "cpp11/integers.hpp"

    [[cpp11::register]]
    int num_odd(cpp11::integers x) {
      int total = 0;
      for (int val : x) {
        if ((val % 2) == 1) {
          ++total;
        }
      }
      return total;
    }
    ', clean = TRUE)
  on.exit(dyn.unload(dll_info[["path"]]))

  expect_equal(num_odd(as.integer(c(1:10, 15, 23))), 7)
})

test_that("cpp_source works with the `file` parameter", {
  skip_on_os("solaris")
  tf <- tempfile(fileext = ".cpp")
  writeLines(
    "[[cpp11::register]]
    bool always_true() {
      return true;
    }
    ", tf)
  on.exit(unlink(tf))

  dll_info <- cpp_source(tf, clean = TRUE, quiet = TRUE)
  on.exit(dyn.unload(dll_info[["path"]]), add = TRUE)

  expect_true(always_true())
})

test_that("cpp_source lets you set the C++ standard", {
  skip_on_os("solaris")
  skip_on_os("windows") # Older windows toolchains do not support C++14
  tf <- tempfile(fileext = ".cpp")
  writeLines(
    '#include <string>
    using namespace std::string_literals;
    [[cpp11::register]]
    std::string fun() {
      auto str = "hello_world"s;
      return str;
    }
    ', tf)
  on.exit(unlink(tf))

  dll_info <- cpp_source(tf, clean = TRUE, quiet = TRUE, cxx_std = "CXX14")
  on.exit(dyn.unload(dll_info[["path"]]), add = TRUE)

  expect_equal(fun(), "hello_world")
})

test_that("generate_cpp_path works", {
  d <- tempfile()
  dir.create(d)
  on.exit(unlink(d, recursive = TRUE))

  expect_equal(
    generate_cpp_path(d),
    normalizePath(file.path(d, "src", "cpp11.cpp"), mustWork = FALSE)
  )

  dir.create(file.path(d, "src"))
  file.create(file.path(d, "src", "cpp11.cpp"))

  expect_equal(
    generate_cpp_path(d),
    normalizePath(file.path(d, "src", "cpp11-2.cpp"), mustWork = FALSE)
  )

  file.create(file.path(d, "src", "cpp11-2.cpp"))

  expect_equal(
    generate_cpp_path(d),
    normalizePath(file.path(d, "src", "cpp11-3.cpp"), mustWork = FALSE)
  )
})
