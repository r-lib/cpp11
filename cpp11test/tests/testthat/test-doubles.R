test_that("doubles iterators work with normal vectors", {

  len <- 1e5
  set.seed(42)
  x <- rnorm(len)
  sum_base <- sum(x)

  expect_equal(sum_dbl_for_(x), sum_base)
  expect_equal(sum_dbl_foreach_(x), sum_base)
  expect_equal(sum_dbl_accumulate_(x), sum_base)
  expect_equal(sum_dbl_for2_(x), sum_base)
})

test_that("doubles iterators work with altrep vectors", {

  len <- 1e5
  seq_double <- function(x) as.double(seq_len(x))

  x <- seq_double(len)

  sum_base <- sum(x)

  expect_equal(sum_dbl_for_(x), sum_base)
  expect_equal(sum_dbl_foreach_(x), sum_base)
  expect_equal(sum_dbl_accumulate_(x), sum_base)
  expect_equal(sum_dbl_for2_(x), sum_base)
})

test_that("writable::doubles grow", {
  len <- 1e5L
  expect_equal(grow_(len), as.numeric(seq(0, len - 1)))
})
