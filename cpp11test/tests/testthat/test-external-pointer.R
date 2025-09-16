# Pacha: test that nullable external pointer is consistent (#312)
test_that("nullable external pointer is consistent", {

  len <- 1e5
  set.seed(42)
  x <- rnorm(len)
  sum_base <- sum(x)

  expect_equal(nullable_extptr_1(), NULL)
  expect_equal(nullable_extptr_2(), NULL)
})
