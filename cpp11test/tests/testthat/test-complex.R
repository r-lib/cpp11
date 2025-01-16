test_that("complex iterators work with normal vectors", {
  len <- 1e5
  set.seed(42)
  x <- complex(real = rnorm(len), imaginary = rnorm(len))
  sum_base <- sum(x)

  # Pacha: I know this is redundant, but exhanging equivalent types
  # allowed me to test for errors in the implementation
  expect_equal(sum_cplx_for_(x), sum_base)
  expect_equal(sum_cplx_for_2_(x), sum_base)
  expect_equal(sum_cplx_for_3_(x), sum_base)
  expect_equal(sum_cplx_for_4_(x), sum_base)
  expect_equal(sum_cplx_for_5_(x), sum_base)
  expect_equal(sum_cplx_for_6_(x), sum_base)

  expect_equal(sum_cplx_foreach_(x), sum_base)
  expect_equal(sum_cplx_accumulate_(x), sum_base)
  expect_equal(sum_cplx_for2_(x), sum_base)
})

test_that("complex iterators work with altrep vectors", {
  len <- 1e5
  seq_complex <- function(x) complex(real = as.double(seq_len(x)), imaginary = as.double(seq_len(x)))

  x <- seq_complex(len)

  sum_base <- sum(x)

  expect_equal(sum_cplx_for_(x), sum_base)
  expect_equal(sum_cplx_foreach_(x), sum_base)
  expect_equal(sum_cplx_accumulate_(x), sum_base)
  expect_equal(sum_cplx_for2_(x), sum_base)
})

test_that("writable::complex grow", {
  len <- 1e5L
  expect_equal(grow_cplx_(len), complex(
    real = as.numeric(seq(0, len - 1)),
    imaginary = as.numeric(seq(0, len - 1))
  ))
})
