This is a follow up patch release that fixes a regression that caused the tidyr
reverse dependency to fail during installation.

I apologize for not catching this before submission, I tested the tidyr
installation interactively and the issue was in the cpp11 code generation. When
run interactively the code generation is automatically regenerated, so I did
not observe the issue.

## Test environments

* GitHub Actions (ubuntu-16.04): 3.3, 3.4, 3.5, oldrel, release, devel
* GitHub Actions (windows): release
* Github Actions (macOS): release, devel
* win-builder: devel

## R CMD check results

0 errors | 0 warnings | 0 note
