test_that("equivalently templated `cpp11::stop()` and `cpp11::warning()` can coexist (#491)", {
  # It is important the the C++ files be named `template-1-stop` and
  # `template-2-warn` because the `cpp11::stop()` call needs to be linked in
  # before the `cpp11::warning()` call to reproduce the original issue,
  # otherwise the templates underlying `cpp11::warning()` will get instantiated
  # first and be reused in `cpp11::stop()` via ODR and that "works" fine.
  expect_snapshot(error = TRUE, {
    test_template_stop()
  })
  expect_snapshot({
    test_template_warning()
  })
})
