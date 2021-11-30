## Current state

The state of cpp11 is pretty stable, it seems to have the features we need for most of our projects using C++.

## Known outstanding issues

### Running the cpp11test tests

Most of the test suite is in a sub-package, cpp11test.
Probably the best way to run these tests is to install the development version of cpp11 and then run `devtools::test()` to run the cpp11test test suite.

If tests failures occur the output from Catch isn't always easy to interpret.
I have a branch of testthat https://github.com/jimhester/testthat/tree/catch-detailed-output that should make things easier to understand.
I contributed those changes to the main testthat, but something changed after merging the more detailed output was lost, I unfortunately never had the time to track down the cause and fix it.

In addition getting a debugger to catch when errors happen can be fiddly when running the cpp11test tests, something about the way that Catch redirects stderr / stdout interacts with the debugger.

The GitHub Actions workflow has some additional logic to handle running the cpp11 tests https://github.com/r-lib/cpp11/blob/fd8ef97d006db847f7f17166cf52e1e0383b2d35/.github/workflows/R-CMD-check.yaml#L95-L102, https://github.com/r-lib/cpp11/blob/fd8ef97d006db847f7f17166cf52e1e0383b2d35/.github/workflows/R-CMD-check.yaml#L117-L124.

### False positive URL checks for git repositories in the vignettes

If you run `urlchecker::url_check()` on the repo you will see the following false positives.

```
! Warning: vignettes/motivations.Rmd:363:11 Moved
git clone https://github.com/r-lib/cpp11.git
          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          https://github.com/r-lib/cpp11
! Warning: vignettes/motivations.Rmd:354:11 Moved
git clone https://github.com/RcppCore/Rcpp.git
          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          https://github.com/RcppCore/Rcpp
>
```

These only happen with the urlchecker package, they can be safely ignored and the real CRAN checks will not show them.


### Ensure you use `Sys.setenv("CPP11_EVAL" = "true"); devtools::submit_cran()` when submitting.

If you forget to set `CPP_EVAL = "true"` then the vignette chunks will not run properly and the vignettes will not be rendered properly.

## Future directions

Some work could be spent in smoothing out the `cpp_source()` / knitr chunk experience.
Our main focus and use cases were in R packages, so that usage is more tested.
Because we don't typically use cpp11 in non package contexts those use cases may not be as nice.

For similar reasons the matrix support might be somewhat lacking, as the majority of our use cases do not deal with numeric matrices.
