## Current state

## Known outstanding issues

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
