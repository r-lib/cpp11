test_that("cpp11::stop formatting works", {
  test1 <- 4
  expect_error(my_stop("Your number is {}", test1), "Your number is 4", fixed = TRUE)

  test2 <- c(3, 5, 7)
  expect_error(my_stop("You've tested this {} times", test2[1]), "You've tested this 3 times",
               fixed = TRUE)
})
test_that("cpp11::warning formatting works", {
  test1 <- "warning"
  expect_warning(my_warning("This is a {}", test1), "This is a warning", fixed = TRUE)

  test2 <- c("failed", "passed")
  expect_warning(my_warning("You {}", test2[2]), "You passed", fixed = TRUE)
})
