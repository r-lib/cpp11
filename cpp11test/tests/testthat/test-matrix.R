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

test_that("doubles_matrix<> can return a matrix with colnames and rownames", {
  x <- matrix(c(1, 2, 3, 4), nrow = 2, ncol = 2)
  colnames(x) <- letters[1:2]
  rownames(x) <- letters[3:4]

  y <- mat_mat_copy_dimnames(x)
  z <- mat_sexp_copy_dimnames(x)

  expect_equal(x, y)
  expect_equal(x, z)

  r <- mat_mat_create_dimnames()
  expect_equal(rownames(r), c("a", "b"))
  expect_equal(colnames(r), c("c", "d"))
})
