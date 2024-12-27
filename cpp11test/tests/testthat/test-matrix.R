test_that("row_sums gives same result as rowSums", {
  x <- cbind(x1 = 3, x2 = c(4:1, 2:5))
  expect_equal(row_sums(x), rowSums(x))

  # With missing values
  x[4, 2] <- NA
  expect_equal(row_sums(x), rowSums(x))

  y <- cbind(x1 = 3, x2 = c(4:1, 2:5))
  y[3, ] <- NA;
  expect_equal(row_sums(y), rowSums(y))
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

test_that("log_mat_mat returns a matrix with colnames and rownames", {
  x <- matrix(c(1, 2, 3, 4), nrow = 2, ncol = 2)
  colnames(x) <- letters[1:2]
  rownames(x) <- letters[3:4]

  y <- log_mat_mat(x)
  z <- log_mat_sexp(x)
  r <- log(x)
  
  expect_equal(y, r)
  expect_equal(z, r)
})
