# Compile C++ code

`cpp_source()` compiles and loads a single C++ file for use in R.
`cpp_function()` compiles and loads a single function for use in R.
`cpp_eval()` evaluates a single C++ expression and returns the result.

## Usage

``` r
cpp_source(
  file,
  code = NULL,
  env = parent.frame(),
  clean = TRUE,
  quiet = TRUE,
  cxx_std = Sys.getenv("CXX_STD", "CXX11"),
  dir = tempfile()
)

cpp_function(
  code,
  env = parent.frame(),
  clean = TRUE,
  quiet = TRUE,
  cxx_std = Sys.getenv("CXX_STD", "CXX11")
)

cpp_eval(
  code,
  env = parent.frame(),
  clean = TRUE,
  quiet = TRUE,
  cxx_std = Sys.getenv("CXX_STD", "CXX11")
)
```

## Arguments

- file:

  A file containing C++ code to compile

- code:

  If non-null, the C++ code to compile

- env:

  The R environment where the R wrapping functions should be defined.

- clean:

  If `TRUE`, cleanup the files after sourcing

- quiet:

  If 'TRUE\`, do not show compiler output

- cxx_std:

  The C++ standard to use, the `CXX_STD` make macro is set to this
  value. The default value queries the `CXX_STD` environment variable,
  or uses 'CXX11' if unset.

- dir:

  The directory to store the generated source files.
  [`tempfile()`](https://rdrr.io/r/base/tempfile.html) is used by
  default. The directory will be removed if `clean` is `TRUE`.

## Value

For `cpp_source()` and `[cpp_function()]` the results of
[`dyn.load()`](https://rdrr.io/r/base/dynload.html) (invisibly). For
`[cpp_eval()]` the results of the evaluated expression.

## Details

Within C++ code you can use `[[cpp11::linking_to("pkgxyz")]]` to link to
external packages. This is equivalent to putting those packages in the
`LinkingTo` field in a package DESCRIPTION.

## Examples

``` r
cpp_source(
  code = '#include "cpp11/integers.hpp"

  [[cpp11::register]]
  int num_odd(cpp11::integers x) {
    int total = 0;
    for (int val : x) {
      if ((val % 2) == 1) {
        ++total;
      }
    }
    return total;
  }
  ')

num_odd(as.integer(c(1:10, 15, 23)))
#> [1] 7

if (interactive() && require("progress")) {

cpp_source(
  code = '
#include <cpp11/R.hpp>
#include <RProgress.h>

[[cpp11::linking_to("progress")]]

[[cpp11::register]] void
show_progress() {
  RProgress::RProgress pb("Processing [:bar] ETA: :eta");

  pb.tick(0);
  for (int i = 0; i < 100; i++) {
    usleep(2.0 / 100 * 1000000);
    pb.tick();
  }
}
')

show_progress()
}
```
