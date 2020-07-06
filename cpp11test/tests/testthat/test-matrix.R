test_that("row_sums gives same result as rowSums", {
  x <- cbind(x1 = 3, x2 = c(4:1, 2:5))
  expect_equal(row_sums(x), rowSums(x))

  # With missing values
  y <- cbind(x1 = 3, x2 = c(4:1, 2:5))
  y[3, ] <- NA; x[4, 2] <- NA
  expect_equal(row_sums(x), rowSums(x))
})
