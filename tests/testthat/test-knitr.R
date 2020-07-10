describe("eng_cpp11", {
  it("works when code is not evaluated", {
    skip_on_os("solaris")
    opts <- knitr::opts_chunk$get()
    opts <- utils::modifyList(opts, list(eval = FALSE, engine = "cpp11", code = "1 + 1"))

    expect_equal(
      eng_cpp11(opts),
      "1 + 1"
    )
  })

  it("works when code is evaluated", {
    skip_on_os("solaris")
    opts <- knitr::opts_chunk$get()
    code <- "[[cpp11::register]] int foo() { return 0; }"
    opts <- utils::modifyList(opts, list(eval = TRUE, engine = "cpp11", code = code, quiet = TRUE))

    expect_equal(
      eng_cpp11(opts),
      code
    )
  })
})
