We cannot use a runnable example for cpp_source as doing so would load a DLL in
to the R session, which is likely undesired when running examples on CRAN's servers.

## Test environments

* GitHub Actions (ubuntu-16.04): 3.3, 3.4, 3.5, oldrel, release, devel
* GitHub Actions (windows): release
* Github Actions (macOS): release, devel
* win-builder: devel

## R CMD check results

0 errors | 0 warnings | 1 note

* This is a new release.
