test_that("row_sums gives same result as rowSums", {
  x <- cbind(x1 = 3, x2 = c(4:1, 2:5))
  expect_equal(row_sums(x), rowSums(x))

  # With missing values
  x[4, 2] <- NA
  expect_equal(row_sums(x), rowSums(x))

  y <- cbind(x1 = 3, x2 = c(4:1, 2:5))
  y[3, ] <- NA;
  expect_equal(row_sums(y), rowSums(y))

  # Pacha: test dgeMatrix and other d**Matrix (Matrix package)

  z <- cbind(x1 = 3, x2 = c(4, 4))
  z2 <- Matrix::Matrix(z) # dgeMatrix
  expect_equal(rowSums(z), row_sums_2(z2))

  z3 <- matrix(c(1, 2, 2, 1), nrow = 2)
  z4 <- new("dsyMatrix", Dim = c(2L, 2L), x = c(1, 2, 2, 1))
  expect_equal(rowSums(z3), row_sums_3(z4))
})

test_that("col_sums gives same result as colSums", {
  x <- cbind(3, c(4:1, 2:5))
  expect_equal(col_sums(x), colSums(x))

  # With missing values
  x[4, 2] <- NA
  expect_equal(col_sums(x), colSums(x))

  y <- cbind(3, c(4:1, 2:5))
  y[3, ] <- NA;
  expect_equal(col_sums(y), colSums(y))
})
