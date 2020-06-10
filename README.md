# cpp11

<!-- badges: start -->
[![R build status](https://github.com/r-lib/cpp11/workflows/R-CMD-check/badge.svg)](https://github.com/r-lib/cpp11/actions)
[![codecov](https://codecov.io/gh/r-lib/cpp11/branch/master/graph/badge.svg?token=EEWYoCYxQ2)](https://codecov.io/gh/r-lib/cpp11)
<!-- badges: end -->

cpp11 is a header-only R package that helps R package developers handle R objects with C++ code.
Its goals and syntax are similar to the excellent [Rcpp](https://cran.r-project.org/package=Rcpp) package.

## Getting started

See [vignette("cpp11")](vignettes/cpp11.Rmd) to get started using cpp11.

## Motivations

[Rcpp](https://cran.r-project.org/package=Rcpp) has been a widely successful project, however over the years a number of issues and additional C++ features have arisen.
Adding these features to Rcpp would require a great deal work, or in some cases would be impossible without severely breaking backwards compatibility.

**cpp11** is a ground up rewrite of C++ bindings to R with different design trade-offs and features.

Changes that motivated cpp11 include:

- Enforcing [copy-on-write semantics](vignettes/motivations.Rmd#copy-on-write-semantics).
- Improving the [safety](vignettes/motivations.Rmd#improve-safety) of using the R API from C++ code.
- Supporting [ALTREP objects](vignettes/motivations.Rmd#altrep-support).
- Using [UTF-8 strings](vignettes/motivations.Rmd#utf-8-everywhere) everywhere.
- Applying newer [C++11 features](vignettes/motivations.Rmd#c11-features).
- Having a more straightforward, [simpler implementation](vignettes/motivations.Rmd#simpler-implementation).
- Faster [compilation time](vignettes/motivations.Rmd#compilation-speed) with lower memory requirements.
- Being *completely* [header only](vignettes/motivations.Rmd#header-only) to avoid ABI issues.
- More robust [protection](vignettes/motivations.Rmd#protection) using a much more efficient linked list data structure.
- [Growing vectors](vignettes/motivations.Rmd#growing-vectors) more efficiently.

See [vignette("motivations")](vignettes/motivations.Rmd) for full details on the motivations for writing cpp11.

## Conversion from Rcpp

See [vignette("converting")](vignettes/converting.Rmd) if you are already familiar with Rcpp or have an existing package that uses Rcpp and want to convert it to use cpp11.

## Internals

See [vignette("internals")](vignettes/internals.Rmd) for details on the cpp11 implementation or if you would like to contribute to cpp11.

## Thanks

cpp11 would not exist without Rcpp.
Thanks to the Rcpp authors, Dirk Eddelbuettel, Romain Francois, JJ Allaire, Kevin Ushey, Qiang Kou, Nathan Russell, Douglas Bates and John Chambers for their work writing and maintaining Rcpp.
