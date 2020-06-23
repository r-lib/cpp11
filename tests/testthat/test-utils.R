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
