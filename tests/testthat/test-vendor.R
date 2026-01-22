describe("cpp_vendor", {
  it("errors if cpp11 is not installed", {
    pkg <- local_package()
    mockery::stub(cpp_vendor, "system.file", "")
    expect_error(
      cpp_vendor(pkg_path(pkg)),
      "cpp11 is not installed"
    )
  })

  it("vendors cpp11", {
    pkg <- local_package()
    p <- pkg_path(pkg)

    cpp_vendor(pkg_path(pkg))

    expect_true(dir.exists(file.path(p, "inst", "include", "cpp11")))
    expect_true(file.exists(file.path(p, "inst", "include", "cpp11.hpp")))
    expect_true(file.exists(file.path(p, "inst", "include", "cpp11", "declarations.hpp")))

    expect_silent(cpp_unvendor(pkg_path(pkg)))
  })
})
