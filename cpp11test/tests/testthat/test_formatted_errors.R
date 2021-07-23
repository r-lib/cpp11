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
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 3b3ff2861878876c2a942808846b172209a28ab7
test_that("cpp11::message formatting works", {
  test1 <- "message"
  expect_message(my_message("This is a {}", test1), "This is a message", fixed = TRUE)

  test2 <- c("great", "super")
  expect_message(my_message("You're {}", test2[2]), "You're super", fixed = TRUE)
})
<<<<<<< HEAD
=======
>>>>>>> upstream/master
=======
>>>>>>> 3b3ff2861878876c2a942808846b172209a28ab7
test_that("cpp11::stop works without including the fmt library", {
  test1 <- "error"
  expect_error(my_stop_n1fmt("This is a stop"), "This is a stop", fixed = TRUE)
  expect_error(my_stop_n2fmt("This is an %s", test1), "This is an error", fixed = TRUE)
})
test_that("cpp11::warning works without including the fmt library", {
  test1 <- "warning"
  expect_warning(my_warning_n1fmt("This is a warning"), "This is a warning", fixed = TRUE)
  expect_warning(my_warning_n2fmt("This is a %s", test1), "This is a warning", fixed = TRUE)
})
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 3b3ff2861878876c2a942808846b172209a28ab7
test_that("cpp11::message works without including the fmt library", {
  test1 <- "message"
  expect_message(my_message_nfmt("This is a %s", test1), "This is a message", fixed = TRUE)

  test2 <- c("great", "super")
  expect_message(my_message_nfmt("You're %s", test2[2]), "You're super", fixed = TRUE)
<<<<<<< HEAD
})
=======
>>>>>>> upstream/master
=======
})
>>>>>>> 3b3ff2861878876c2a942808846b172209a28ab7
