#include "cpp11/nameof.hpp"

#include <testthat.h>

struct Global;

namespace ns {
struct Namespaced;
}  // namespace ns

context("nameof-C++") {
  test_that("nameof works") {
    expect_true(cpp11::nameof<Global>() == "Global");
    expect_true(cpp11::nameof<ns::Namespaced>() == "ns::Namespaced");
    expect_true(cpp11::nameof<ns::Namespaced>(/*strip_namespace=*/true) == "Namespaced");

    // namespace for local scope structs is compiler dependent
    struct Local;
    expect_true(cpp11::nameof<Local>(/*strip_namespace=*/true) == "Local");
  }
}
