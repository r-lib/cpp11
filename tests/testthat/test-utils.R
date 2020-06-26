describe("cli_suppress", {
  it("suppresses cli outputs", {
    f <- function() cli::cli_text("hi")
    expect_message(f(), "hi")
    expect_message(cli_suppress(f()), NA)
  })
})

describe("glue_collapse_data", {
  it("works with empty inputs", {
    expect_equal(
      glue_collapse_data(mtcars, ""),
      ""
    )

    expect_equal(
      glue_collapse_data(mtcars[FALSE, ], "{hp}"),
      ""
    )
  })

  it("works with non-empty inputs", {
    expect_equal(
      glue_collapse_data(mtcars[1, ], "{hp}"),
      "110"
    )

    expect_equal(
      glue_collapse_data(mtcars[1:2, ], "{hp}"),
      "110, 110"
    )
  })
})

describe("stop_unless_installed", {
  mockery::stub(stop_unless_installed, "requireNamespace", FALSE)

  expect_error(
    stop_unless_installed("foo"),
    "The foo package\\(s\\) are required for this functionality"
  )
})
