# Vendor the cpp11 dependency

Vendoring is the act of making your own copy of the 3rd party packages
your project is using. It is often used in the go language community.

## Usage

``` r
cpp_vendor(path = ".")
```

## Arguments

- path:

  The path to the package root directory

## Value

The file path to the vendored code (invisibly).

## Details

This function vendors cpp11 into your package by copying the cpp11
headers into the `inst/include` folder of your package and adding 'cpp11
version: XYZ' to the top of the files, where XYZ is the version of cpp11
currently installed on your machine.

If you choose to vendor the headers you should *remove*
`LinkingTo: cpp11` from your DESCRIPTION.

**Note**: vendoring places the responsibility of updating the code on
**you**. Bugfixes and new features in cpp11 will not be available for
your code until you run `cpp_vendor()` again.

## Examples

``` r
# create a new directory
dir <- tempfile()
dir.create(dir)

# vendor the cpp11 headers into the directory
cpp_vendor(dir)

list.files(file.path(dir, "inst", "include", "cpp11"))
#>  [1] "R.hpp"                "altrep.hpp"          
#>  [3] "as.hpp"               "attribute_proxy.hpp" 
#>  [5] "data_frame.hpp"       "declarations.hpp"    
#>  [7] "doubles.hpp"          "environment.hpp"     
#>  [9] "external_pointer.hpp" "function.hpp"        
#> [11] "integers.hpp"         "list.hpp"            
#> [13] "list_of.hpp"          "logicals.hpp"        
#> [15] "matrix.hpp"           "named_arg.hpp"       
#> [17] "protect.hpp"          "r_bool.hpp"          
#> [19] "r_string.hpp"         "r_vector.hpp"        
#> [21] "raws.hpp"             "sexp.hpp"            
#> [23] "strings.hpp"         

# cleanup
unlink(dir, recursive = TRUE)
```
