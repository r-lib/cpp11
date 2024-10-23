test_that("cpp_vendor errors if cpp11 is not installed", {
  pkg <- local_package()

  expect_error(
    cpp_vendor(pkg_path(pkg), headers = ""),
    "cpp11 is not installed"
  )
})

test_that("cpp_vendor errors if cpp11 is already vendored", {
  pkg <- local_package()
  cpp_vendor(pkg_path(pkg))

  expect_error(
    cpp_vendor(pkg_path(pkg)),
    "already exists"
  )
})

test_that("cpp_vendor vendors cpp11", {
  pkg <- local_package()
  p <- pkg_path(pkg)

  cpp_vendor(pkg_path(pkg))

  expect_true(dir.exists(file.path(p, "inst", "include", "cpp11")))
  expect_true(file.exists(file.path(p, "inst", "include", "cpp11.hpp")))
  expect_true(file.exists(file.path(p, "inst", "include", "cpp11", "declarations.hpp")))
})
