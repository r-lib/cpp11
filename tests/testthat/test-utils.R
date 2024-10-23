test_that("glue_collapse_data works with empty inputs", {
  expect_equal(
    glue_collapse_data(mtcars, ""),
    ""
  )

  expect_equal(
    glue_collapse_data(mtcars[FALSE, ], "{hp}"),
    ""
  )
})

test_that("glue_collapse_data works with non-empty inputs", {
  expect_equal(
    glue_collapse_data(mtcars[1, ], "{hp}"),
    "110"
  )

  expect_equal(
    glue_collapse_data(mtcars[1:2, ], "{hp}"),
    "110, 110"
  )
})

test_that("stop_unless_installed errors when package is not installed", {
  original_requireNamespace <- requireNamespace

  # Temporarily override requireNamespace to simulate the package not being installed
  requireNamespace <- function(...) FALSE
  on.exit(requireNamespace <- original_requireNamespace, add = TRUE)

  expect_error(
    stop_unless_installed("foo"),
    "The foo package\\(s\\) are required for this functionality"
  )
})
