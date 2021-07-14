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

test_that("cpp_source works with files called `cpp11.cpp`", {
  skip_on_os("solaris")
  tf <- file.path(tempdir(), "cpp11.cpp")
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

test_that("cpp_source returns original file name on error", {

  expect_output(try(cpp_source(test_path("single_error.cpp"), clean = TRUE), silent = TRUE),
               normalizePath(test_path("single_error.cpp"), winslash = "/"), fixed = TRUE)

  #error generated for incorrect attributes is separate from compilation errors
  expect_error(cpp_source(test_path("single_incorrect.cpp"), clean = TRUE),
                normalizePath(test_path("single_incorrect.cpp"), winslash = "/"), fixed = TRUE)

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

test_that("generate_cpp_name works", {
  expect_equal(
    generate_cpp_name("foo.cpp"),
    "foo.cpp"
  )

  expect_equal(
    generate_cpp_name("foo.cpp", loaded_dlls = "foo"),
    "foo_2.cpp"
  )

expect_equal(
  generate_cpp_name("foo.cpp", loaded_dlls = c("foo", "foo_2")),
  "foo_3.cpp"
  )
})

test_that("generate_include_paths handles paths with spaces", {
  if (is_windows()) {
    mockery::stub(generate_include_paths, "system.file", "C:\\a path with spaces\\cpp11")
    expect_equal(generate_include_paths("cpp11"), "-I\"C:\\a path with spaces\\cpp11\"")
  } else {
    mockery::stub(generate_include_paths, "system.file", "/a path with spaces/cpp11")
    expect_equal(generate_include_paths("cpp11"), "-I'/a path with spaces/cpp11'")
  }
})

test_that("check_valid_attributes does not return an error if all registers are correct", {
  expect_error_free(
    cpp11::cpp_source(clean = TRUE, code = '#include <cpp11.hpp>
  using namespace cpp11::literals;
  [[cpp11::register]]
  cpp11::list fn() {
    cpp11::writable::list x;
    x.push_back({"foo"_nm = 1});
    return x;
  }
 [[cpp11::register]]
  cpp11::list fn2() {
    cpp11::writable::list x;
    x.push_back({"foo"_nm = 1});
    return x;
  }'))
  expect_error_free(
    cpp11::cpp_source(clean = TRUE,
      code = '#include <cpp11/R.hpp>
              #include <RProgress.h>

              [[cpp11::linking_to("progress")]]

              [[cpp11::register]] void show_progress() {
                RProgress::RProgress pb("Processing [:bar] ETA: :eta");

                pb.tick(0);
                for (int i = 0; i < 100; i++) {
                  usleep(2.0 / 100 * 1000000);
                  pb.tick();
                }
              }
              ')
  )
})

test_that("check_valid_attributes returns an error if one or more registers is incorrect", {
  expect_error(
    cpp11::cpp_source(code = '#include <cpp11.hpp>
  using namespace cpp11::literals;
  [[cpp11::reg]]
  cpp11::list fn() {
    cpp11::writable::list x;
    x.push_back({"foo"_nm = 1});
    return x;
  }
 [[cpp11::register]]
  cpp11::list fn2() {
    cpp11::writable::list x;
    x.push_back({"foo"_nm = 1});
    return x;
  }'))

  expect_error(
    cpp11::cpp_source(code = '#include <cpp11.hpp>
  using namespace cpp11::literals;
  [[cpp11::reg]]
  cpp11::list fn() {
    cpp11::writable::list x;
    x.push_back({"foo"_nm = 1});
    return x;
  }'))

  expect_error(
    cpp11::cpp_source(code = '#include <cpp11.hpp>
  using namespace cpp11::literals;
  [[cpp11::reg]]
  cpp11::list fn() {
    cpp11::writable::list x;
    x.push_back({"foo"_nm = 1});
    return x;
  }
 [[cpp11::egister]]
  cpp11::list fn2() {
    cpp11::writable::list x;
    x.push_back({"foo"_nm = 1});
    return x;
  }'))



  expect_error(
    cpp11::cpp_source(
      code = '
      #include <cpp11/R.hpp>
      #include <RProgress.h>
      [[cpp11::link_to("progress")]]
      [[cpp11::register]] void show_progress() {
        RProgress::RProgress pb("Processing [:bar] ETA: :eta");
        pb.tick(0);
        for (int i = 0; i < 100; i++) {
          usleep(2.0 / 100 * 1000000);
          pb.tick();
        }
      }
'))
})

test_that("cpp_source(d) functions work after sourcing file more than once", {
  cpp11::cpp_source(test_path("single.cpp"), clean = TRUE)
  expect_equal(foo(), 1)
  cpp11::cpp_source(test_path("single.cpp"), clean = TRUE)
  expect_equal(foo(), 1)
})
