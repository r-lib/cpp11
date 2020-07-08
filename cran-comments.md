We cannot use a runnable example for cpp_source as doing so would load a DLL in
to the R session, which is likely undesired when running examples on CRAN's servers.

## Test environments
* local R installation, R 4.0.0
* ubuntu 16.04 (on GitHub Actions), R 4.0, 3.6, 3.5, 3.4, 3.3
* win-builder (devel)

## R CMD check results

0 errors | 0 warnings | 1 note

* This is a new release.
