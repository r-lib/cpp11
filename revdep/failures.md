# CytoML

<details>

* Version: 2.12.0
* GitHub: https://github.com/RGLab/CytoML
* Source code: https://github.com/cran/CytoML
* Date/Publication: 2023-04-25
* Number of recursive dependencies: 107

Run `revdepcheck::revdep_details(, "CytoML")` for more info

</details>

## In both

*   checking whether package ‘CytoML’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/CytoML/new/CytoML.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘CytoML’ ...
** using staged installation
checking whether the C++ compiler works... yes
checking for C++ compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether we are using the GNU C++ compiler... yes
checking whether clang++ -arch arm64 -std=gnu++11 accepts -g... yes
checking for gcc... clang -arch arm64
...
../inst/include/CytoML/winFlowJoWorkspace.hpp:435:30: warning: '/*' within block comment [-Wcomment]
           * "*[local-name()='edge']/*[local-name()='vertex']" is for ellipsoidGate
                                    ^
3 warnings generated.
clang++ -arch arm64 -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o CytoML.so cpp11.o parseFlowJoWorkspace.o /Users/romainfrancois/git/cpp11/revdep/library.noindex/CytoML/cytolib/lib/libcytolib.a /Users/romainfrancois/git/cpp11/revdep/library.noindex/CytoML/Rhdf5lib/lib/libhdf5_cpp.a /Users/romainfrancois/git/cpp11/revdep/library.noindex/CytoML/Rhdf5lib/lib/libhdf5.a -L/Users/romainfrancois/git/cpp11/revdep/library.noindex/CytoML/Rhdf5lib/lib -lcrypto -lcurl -lsz -laec -lz -ldl -lm -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRlapack -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRblas -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lxml2 -lz -lpthread -licucore -lm -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
ld: library not found for -lcrypto
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [CytoML.so] Error 1
ERROR: compilation failed for package ‘CytoML’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/CytoML/new/CytoML.Rcheck/CytoML’


```
### CRAN

```
* installing *source* package ‘CytoML’ ...
** using staged installation
checking whether the C++ compiler works... yes
checking for C++ compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether we are using the GNU C++ compiler... yes
checking whether clang++ -arch arm64 -std=gnu++11 accepts -g... yes
checking for gcc... clang -arch arm64
...
../inst/include/CytoML/winFlowJoWorkspace.hpp:435:30: warning: '/*' within block comment [-Wcomment]
           * "*[local-name()='edge']/*[local-name()='vertex']" is for ellipsoidGate
                                    ^
3 warnings generated.
clang++ -arch arm64 -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o CytoML.so cpp11.o parseFlowJoWorkspace.o /Users/romainfrancois/git/cpp11/revdep/library.noindex/CytoML/cytolib/lib/libcytolib.a /Users/romainfrancois/git/cpp11/revdep/library.noindex/CytoML/Rhdf5lib/lib/libhdf5_cpp.a /Users/romainfrancois/git/cpp11/revdep/library.noindex/CytoML/Rhdf5lib/lib/libhdf5.a -L/Users/romainfrancois/git/cpp11/revdep/library.noindex/CytoML/Rhdf5lib/lib -lcrypto -lcurl -lsz -laec -lz -ldl -lm -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRlapack -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRblas -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lxml2 -lz -lpthread -licucore -lm -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
ld: library not found for -lcrypto
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [CytoML.so] Error 1
ERROR: compilation failed for package ‘CytoML’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/CytoML/old/CytoML.Rcheck/CytoML’


```
# epiworldR

<details>

* Version: 0.0-2
* GitHub: https://github.com/UofUEpiBio/epiworldR
* Source code: https://github.com/cran/epiworldR
* Date/Publication: 2023-06-21 23:00:07 UTC
* Number of recursive dependencies: 46

Run `revdepcheck::revdep_details(, "epiworldR")` for more info

</details>

## In both

*   checking whether package ‘epiworldR’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/epiworldR/new/epiworldR.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘epiworldR’ ...
** package ‘epiworldR’ successfully unpacked and MD5 sums checked
** using staged installation
checking whether the C++ compiler works... yes
checking for C++ compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether the compiler supports GNU C++... yes
checking whether clang++ -arch arm64 -std=gnu++17 accepts -g... yes
...
          ^
1 warning generated.
clang++ -arch arm64 -std=gnu++17 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o epiworldR.so actions.o agents.o cpp11.o db.o epimodels.o model.o tool.o virus.o -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRlapack -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRblas -L/opt/gfortran/lib/gcc/aarch64-apple-darwin20.0/12.2.0 -L/opt/gfortran/lib -lgfortran -lemutls_w -lquadmath -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
ld: warning: directory not found for option '-L/opt/gfortran/lib/gcc/aarch64-apple-darwin20.0/12.2.0'
ld: warning: directory not found for option '-L/opt/gfortran/lib'
ld: library not found for -lgfortran
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [epiworldR.so] Error 1
ERROR: compilation failed for package ‘epiworldR’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/epiworldR/new/epiworldR.Rcheck/epiworldR’


```
### CRAN

```
* installing *source* package ‘epiworldR’ ...
** package ‘epiworldR’ successfully unpacked and MD5 sums checked
** using staged installation
checking whether the C++ compiler works... yes
checking for C++ compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether the compiler supports GNU C++... yes
checking whether clang++ -arch arm64 -std=gnu++17 accepts -g... yes
...
          ^
1 warning generated.
clang++ -arch arm64 -std=gnu++17 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o epiworldR.so actions.o agents.o cpp11.o db.o epimodels.o model.o tool.o virus.o -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRlapack -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRblas -L/opt/gfortran/lib/gcc/aarch64-apple-darwin20.0/12.2.0 -L/opt/gfortran/lib -lgfortran -lemutls_w -lquadmath -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
ld: warning: directory not found for option '-L/opt/gfortran/lib/gcc/aarch64-apple-darwin20.0/12.2.0'
ld: warning: directory not found for option '-L/opt/gfortran/lib'
ld: library not found for -lgfortran
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [epiworldR.so] Error 1
ERROR: compilation failed for package ‘epiworldR’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/epiworldR/old/epiworldR.Rcheck/epiworldR’


```
# flowWorkspace

<details>

* Version: 4.12.0
* GitHub: NA
* Source code: https://github.com/cran/flowWorkspace
* Date/Publication: 2023-04-25
* Number of recursive dependencies: 107

Run `revdepcheck::revdep_details(, "flowWorkspace")` for more info

</details>

## In both

*   checking whether package ‘flowWorkspace’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/flowWorkspace/new/flowWorkspace.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘flowWorkspace’ ...
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++11
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c R_API.cpp -o R_API.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c R_GatingHierarchy.cpp -o R_GatingHierarchy.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c R_GatingSet.cpp -o R_GatingSet.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c cpp11.cpp -o cpp11.o
...
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c getPopStats.cpp -o getPopStats.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c getSingleCellExpression.cpp -o getSingleCellExpression.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c h5_error_r_handler.cpp -o h5_error_r_handler.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c setCounts.cpp -o setCounts.o
clang++ -arch arm64 -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o flowWorkspace.so R_API.o R_GatingHierarchy.o R_GatingSet.o cpp11.o cytoframeAPI.o cytosetAPI.o getDescendants.o getPopStats.o getSingleCellExpression.o h5_error_r_handler.o setCounts.o /Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/lib/libcytolib.a /Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/lib/libhdf5_cpp.a /Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/lib/libhdf5.a -L/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/lib -lcrypto -lcurl -lsz -laec -lz -ldl -lm -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRlapack -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRblas -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
ld: library not found for -lcrypto
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [flowWorkspace.so] Error 1
ERROR: compilation failed for package ‘flowWorkspace’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/flowWorkspace/new/flowWorkspace.Rcheck/flowWorkspace’


```
### CRAN

```
* installing *source* package ‘flowWorkspace’ ...
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++11
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c R_API.cpp -o R_API.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c R_GatingHierarchy.cpp -o R_GatingHierarchy.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c R_GatingSet.cpp -o R_GatingSet.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c cpp11.cpp -o cpp11.o
...
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c getPopStats.cpp -o getPopStats.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c getSingleCellExpression.cpp -o getSingleCellExpression.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c h5_error_r_handler.cpp -o h5_error_r_handler.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DROUT -I../inst/include -DBOOST_NO_AUTO_PTR -Wno-pedantic -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/RProtoBufLib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c setCounts.cpp -o setCounts.o
clang++ -arch arm64 -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o flowWorkspace.so R_API.o R_GatingHierarchy.o R_GatingSet.o cpp11.o cytoframeAPI.o cytosetAPI.o getDescendants.o getPopStats.o getSingleCellExpression.o h5_error_r_handler.o setCounts.o /Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/cytolib/lib/libcytolib.a /Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/lib/libhdf5_cpp.a /Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/lib/libhdf5.a -L/Users/romainfrancois/git/cpp11/revdep/library.noindex/flowWorkspace/Rhdf5lib/lib -lcrypto -lcurl -lsz -laec -lz -ldl -lm -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRlapack -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRblas -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
ld: library not found for -lcrypto
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [flowWorkspace.so] Error 1
ERROR: compilation failed for package ‘flowWorkspace’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/flowWorkspace/old/flowWorkspace.Rcheck/flowWorkspace’


```
# hilbert

<details>

* Version: 0.2.1
* GitHub: https://github.com/program--/hilbert
* Source code: https://github.com/cran/hilbert
* Date/Publication: 2022-04-08 08:42:30 UTC
* Number of recursive dependencies: 61

Run `revdepcheck::revdep_details(, "hilbert")` for more info

</details>

## In both

*   checking whether package ‘hilbert’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/hilbert/new/hilbert.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘hilbert’ ...
** package ‘hilbert’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++11
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -I../inst/include -fPIC  -Wall -O3 -c cpp11.cpp -o cpp11.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -I../inst/include -fPIC  -Wall -O3 -c hilbert-interface.cpp -o hilbert-interface.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -I../inst/include -fPIC  -Wall -O3 -c hilbert-interface64.cpp -o hilbert-interface64.o
clang++ -arch arm64 -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o hilbert.so cpp11.o hilbert-interface.o hilbert-interface64.o -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRlapack -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRblas -L/opt/gfortran/lib/gcc/aarch64-apple-darwin20.0/12.2.0 -L/opt/gfortran/lib -lgfortran -lemutls_w -lquadmath -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
ld: warning: directory not found for option '-L/opt/gfortran/lib/gcc/aarch64-apple-darwin20.0/12.2.0'
ld: warning: directory not found for option '-L/opt/gfortran/lib'
ld: library not found for -lgfortran
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [hilbert.so] Error 1
ERROR: compilation failed for package ‘hilbert’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/hilbert/new/hilbert.Rcheck/hilbert’


```
### CRAN

```
* installing *source* package ‘hilbert’ ...
** package ‘hilbert’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++11
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -I../inst/include -fPIC  -Wall -O3 -c cpp11.cpp -o cpp11.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -I../inst/include -fPIC  -Wall -O3 -c hilbert-interface.cpp -o hilbert-interface.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -I../inst/include -fPIC  -Wall -O3 -c hilbert-interface64.cpp -o hilbert-interface64.o
clang++ -arch arm64 -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o hilbert.so cpp11.o hilbert-interface.o hilbert-interface64.o -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRlapack -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -lRblas -L/opt/gfortran/lib/gcc/aarch64-apple-darwin20.0/12.2.0 -L/opt/gfortran/lib -lgfortran -lemutls_w -lquadmath -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
ld: warning: directory not found for option '-L/opt/gfortran/lib/gcc/aarch64-apple-darwin20.0/12.2.0'
ld: warning: directory not found for option '-L/opt/gfortran/lib'
ld: library not found for -lgfortran
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [hilbert.so] Error 1
ERROR: compilation failed for package ‘hilbert’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/hilbert/old/hilbert.Rcheck/hilbert’


```
# igraph

<details>

* Version: 1.5.0
* GitHub: https://github.com/igraph/rigraph
* Source code: https://github.com/cran/igraph
* Date/Publication: 2023-06-16 08:30:02 UTC
* Number of recursive dependencies: 71

Run `revdepcheck::revdep_details(, "igraph")` for more info

</details>

## In both

*   checking whether package ‘igraph’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/igraph/new/igraph.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘igraph’ ...
** package ‘igraph’ successfully unpacked and MD5 sums checked
** using staged installation
checking for gcc... clang -arch arm64
checking whether the C compiler works... yes
checking for C compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether the compiler supports GNU C... yes
...
clang -arch arm64 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DUSING_R -I. -Icore -Iinclude -Ivendor -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -DNDEBUG -DNTIMER -DNPRINT -DINTERNAL_ARPACK -DPRPACK_IGRAPH_SUPPORT -DIGRAPH_THREAD_LOCAL=/**/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -fPIC  -O3 -c vendor/plfit/platform.c -o vendor/plfit/platform.o
clang -arch arm64 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DUSING_R -I. -Icore -Iinclude -Ivendor -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -DNDEBUG -DNTIMER -DNPRINT -DINTERNAL_ARPACK -DPRPACK_IGRAPH_SUPPORT -DIGRAPH_THREAD_LOCAL=/**/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -fPIC  -O3 -c vendor/plfit/plfit.c -o vendor/plfit/plfit.o
clang -arch arm64 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DUSING_R -I. -Icore -Iinclude -Ivendor -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -DNDEBUG -DNTIMER -DNPRINT -DINTERNAL_ARPACK -DPRPACK_IGRAPH_SUPPORT -DIGRAPH_THREAD_LOCAL=/**/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -fPIC  -O3 -c vendor/plfit/plfit_error.c -o vendor/plfit/plfit_error.o
clang -arch arm64 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DUSING_R -I. -Icore -Iinclude -Ivendor -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -DNDEBUG -DNTIMER -DNPRINT -DINTERNAL_ARPACK -DPRPACK_IGRAPH_SUPPORT -DIGRAPH_THREAD_LOCAL=/**/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -fPIC  -O3 -c vendor/plfit/rbinom.c -o vendor/plfit/rbinom.o
clang -arch arm64 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DUSING_R -I. -Icore -Iinclude -Ivendor -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -DNDEBUG -DNTIMER -DNPRINT -DINTERNAL_ARPACK -DPRPACK_IGRAPH_SUPPORT -DIGRAPH_THREAD_LOCAL=/**/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -fPIC  -O3 -c vendor/plfit/sampling.c -o vendor/plfit/sampling.o
/opt/gfortran/bin/gfortran -arch arm64  -fPIC  -Wall -g -O2  -c vendor/arpack/dgetv0.f -o vendor/arpack/dgetv0.o
make: /opt/gfortran/bin/gfortran: No such file or directory
make: *** [vendor/arpack/dgetv0.o] Error 1
ERROR: compilation failed for package ‘igraph’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/igraph/new/igraph.Rcheck/igraph’


```
### CRAN

```
* installing *source* package ‘igraph’ ...
** package ‘igraph’ successfully unpacked and MD5 sums checked
** using staged installation
checking for gcc... clang -arch arm64
checking whether the C compiler works... yes
checking for C compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether the compiler supports GNU C... yes
...
clang -arch arm64 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DUSING_R -I. -Icore -Iinclude -Ivendor -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -DNDEBUG -DNTIMER -DNPRINT -DINTERNAL_ARPACK -DPRPACK_IGRAPH_SUPPORT -DIGRAPH_THREAD_LOCAL=/**/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -fPIC  -O3 -c vendor/plfit/platform.c -o vendor/plfit/platform.o
clang -arch arm64 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DUSING_R -I. -Icore -Iinclude -Ivendor -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -DNDEBUG -DNTIMER -DNPRINT -DINTERNAL_ARPACK -DPRPACK_IGRAPH_SUPPORT -DIGRAPH_THREAD_LOCAL=/**/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -fPIC  -O3 -c vendor/plfit/plfit.c -o vendor/plfit/plfit.o
clang -arch arm64 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DUSING_R -I. -Icore -Iinclude -Ivendor -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -DNDEBUG -DNTIMER -DNPRINT -DINTERNAL_ARPACK -DPRPACK_IGRAPH_SUPPORT -DIGRAPH_THREAD_LOCAL=/**/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -fPIC  -O3 -c vendor/plfit/plfit_error.c -o vendor/plfit/plfit_error.o
clang -arch arm64 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DUSING_R -I. -Icore -Iinclude -Ivendor -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -DNDEBUG -DNTIMER -DNPRINT -DINTERNAL_ARPACK -DPRPACK_IGRAPH_SUPPORT -DIGRAPH_THREAD_LOCAL=/**/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -fPIC  -O3 -c vendor/plfit/rbinom.c -o vendor/plfit/rbinom.o
clang -arch arm64 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -DUSING_R -I. -Icore -Iinclude -Ivendor -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -DNDEBUG -DNTIMER -DNPRINT -DINTERNAL_ARPACK -DPRPACK_IGRAPH_SUPPORT -DIGRAPH_THREAD_LOCAL=/**/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -fPIC  -O3 -c vendor/plfit/sampling.c -o vendor/plfit/sampling.o
/opt/gfortran/bin/gfortran -arch arm64  -fPIC  -Wall -g -O2  -c vendor/arpack/dgetv0.f -o vendor/arpack/dgetv0.o
make: /opt/gfortran/bin/gfortran: No such file or directory
make: *** [vendor/arpack/dgetv0.o] Error 1
ERROR: compilation failed for package ‘igraph’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/igraph/old/igraph.Rcheck/igraph’


```
# ncdfFlow

<details>

* Version: 2.46.0
* GitHub: NA
* Source code: https://github.com/cran/ncdfFlow
* Date/Publication: 2023-04-25
* Number of recursive dependencies: 111

Run `revdepcheck::revdep_details(, "ncdfFlow")` for more info

</details>

## In both

*   checking whether package ‘ncdfFlow’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/ncdfFlow/new/ncdfFlow.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘ncdfFlow’ ...
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++11
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c cpp11.cpp -o cpp11.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c hdfFlow.cpp -o hdfFlow.o
hdfFlow.cpp:493:14: warning: variable 'status' set but not used [-Wunused-but-set-variable]
        herr_t      status;
...
1 warning generated.
mkdir -p "/Users/romainfrancois/git/cpp11/revdep/checks.noindex/ncdfFlow/new/ncdfFlow.Rcheck/00LOCK-ncdfFlow/00new/ncdfFlow/lib"
ar rs "/Users/romainfrancois/git/cpp11/revdep/checks.noindex/ncdfFlow/new/ncdfFlow.Rcheck/00LOCK-ncdfFlow/00new/ncdfFlow/lib/libncdfFlow.a" cpp11.o hdfFlow.o
ar: creating archive /Users/romainfrancois/git/cpp11/revdep/checks.noindex/ncdfFlow/new/ncdfFlow.Rcheck/00LOCK-ncdfFlow/00new/ncdfFlow/lib/libncdfFlow.a
clang++ -arch arm64 -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o ncdfFlow.so cpp11.o hdfFlow.o /Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/Rhdf5lib/lib/libhdf5_cpp.a /Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/Rhdf5lib/lib/libhdf5.a -L/Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/Rhdf5lib/lib -lcrypto -lcurl -lsz -laec -lz -ldl -lm -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
ld: library not found for -lcrypto
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [ncdfFlow.so] Error 1
ERROR: compilation failed for package ‘ncdfFlow’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/ncdfFlow/new/ncdfFlow.Rcheck/ncdfFlow’


```
### CRAN

```
* installing *source* package ‘ncdfFlow’ ...
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++11
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c cpp11.cpp -o cpp11.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/BH/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/Rhdf5lib/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c hdfFlow.cpp -o hdfFlow.o
hdfFlow.cpp:493:14: warning: variable 'status' set but not used [-Wunused-but-set-variable]
        herr_t      status;
...
1 warning generated.
mkdir -p "/Users/romainfrancois/git/cpp11/revdep/checks.noindex/ncdfFlow/old/ncdfFlow.Rcheck/00LOCK-ncdfFlow/00new/ncdfFlow/lib"
ar rs "/Users/romainfrancois/git/cpp11/revdep/checks.noindex/ncdfFlow/old/ncdfFlow.Rcheck/00LOCK-ncdfFlow/00new/ncdfFlow/lib/libncdfFlow.a" cpp11.o hdfFlow.o
ar: creating archive /Users/romainfrancois/git/cpp11/revdep/checks.noindex/ncdfFlow/old/ncdfFlow.Rcheck/00LOCK-ncdfFlow/00new/ncdfFlow/lib/libncdfFlow.a
clang++ -arch arm64 -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o ncdfFlow.so cpp11.o hdfFlow.o /Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/Rhdf5lib/lib/libhdf5_cpp.a /Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/Rhdf5lib/lib/libhdf5.a -L/Users/romainfrancois/git/cpp11/revdep/library.noindex/ncdfFlow/Rhdf5lib/lib -lcrypto -lcurl -lsz -laec -lz -ldl -lm -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
ld: library not found for -lcrypto
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [ncdfFlow.so] Error 1
ERROR: compilation failed for package ‘ncdfFlow’
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/ncdfFlow/old/ncdfFlow.Rcheck/ncdfFlow’


```
# RcppAlgos

<details>

* Version: 2.7.2
* GitHub: https://github.com/jwood000/RcppAlgos
* Source code: https://github.com/cran/RcppAlgos
* Date/Publication: 2023-02-11 13:40:02 UTC
* Number of recursive dependencies: 62

Run `revdepcheck::revdep_details(, "RcppAlgos")` for more info

</details>

## In both

*   checking whether package ‘RcppAlgos’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/RcppAlgos/new/RcppAlgos.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘RcppAlgos’ ...
** package ‘RcppAlgos’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++17
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++17 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -I../inst/include/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -fPIC  -falign-functions=64 -Wall -g -O2  -c BigComboCount.cpp -o BigComboCount.o
clang++ -arch arm64 -std=gnu++17 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -I../inst/include/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -fPIC  -falign-functions=64 -Wall -g -O2  -c BigPartsCountDistinct.cpp -o BigPartsCountDistinct.o
clang++ -arch arm64 -std=gnu++17 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -I../inst/include/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -fPIC  -falign-functions=64 -Wall -g -O2  -c BigPartsCountRep.cpp -o BigPartsCountRep.o
...
** building package indices
** installing vignettes
** testing if installed package can be loaded from temporary location
Error: package or namespace load failed for ‘RcppAlgos’ in dyn.load(file, DLLpath = DLLpath, ...):
 unable to load shared object '/Users/romainfrancois/git/cpp11/revdep/checks.noindex/RcppAlgos/new/RcppAlgos.Rcheck/00LOCK-RcppAlgos/00new/RcppAlgos/libs/RcppAlgos.so':
  dlopen(/Users/romainfrancois/git/cpp11/revdep/checks.noindex/RcppAlgos/new/RcppAlgos.Rcheck/00LOCK-RcppAlgos/00new/RcppAlgos/libs/RcppAlgos.so, 0x0006): symbol not found in flat namespace '___gmp_get_memory_functions'
Error: loading failed
Execution halted
ERROR: loading failed
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/RcppAlgos/new/RcppAlgos.Rcheck/RcppAlgos’


```
### CRAN

```
* installing *source* package ‘RcppAlgos’ ...
** package ‘RcppAlgos’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++17
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++17 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -I../inst/include/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -fPIC  -falign-functions=64 -Wall -g -O2  -c BigComboCount.cpp -o BigComboCount.o
clang++ -arch arm64 -std=gnu++17 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -I../inst/include/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -fPIC  -falign-functions=64 -Wall -g -O2  -c BigPartsCountDistinct.cpp -o BigPartsCountDistinct.o
clang++ -arch arm64 -std=gnu++17 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG -I../inst/include/ -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -fPIC  -falign-functions=64 -Wall -g -O2  -c BigPartsCountRep.cpp -o BigPartsCountRep.o
...
** building package indices
** installing vignettes
** testing if installed package can be loaded from temporary location
Error: package or namespace load failed for ‘RcppAlgos’ in dyn.load(file, DLLpath = DLLpath, ...):
 unable to load shared object '/Users/romainfrancois/git/cpp11/revdep/checks.noindex/RcppAlgos/old/RcppAlgos.Rcheck/00LOCK-RcppAlgos/00new/RcppAlgos/libs/RcppAlgos.so':
  dlopen(/Users/romainfrancois/git/cpp11/revdep/checks.noindex/RcppAlgos/old/RcppAlgos.Rcheck/00LOCK-RcppAlgos/00new/RcppAlgos/libs/RcppAlgos.so, 0x0006): symbol not found in flat namespace '___gmp_get_memory_functions'
Error: loading failed
Execution halted
ERROR: loading failed
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/RcppAlgos/old/RcppAlgos.Rcheck/RcppAlgos’


```
# spatialsample

<details>

* Version: 0.4.0
* GitHub: https://github.com/tidymodels/spatialsample
* Source code: https://github.com/cran/spatialsample
* Date/Publication: 2023-05-17 15:50:06 UTC
* Number of recursive dependencies: 107

Run `revdepcheck::revdep_details(, "spatialsample")` for more info

</details>

## In both

*   R CMD check timed out
    

# svglite

<details>

* Version: 2.1.1
* GitHub: https://github.com/r-lib/svglite
* Source code: https://github.com/cran/svglite
* Date/Publication: 2023-01-10 09:30:02 UTC
* Number of recursive dependencies: 64

Run `revdepcheck::revdep_details(, "svglite")` for more info

</details>

## In both

*   checking whether package ‘svglite’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/svglite/new/svglite.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘svglite’ ...
** package ‘svglite’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++11
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/svglite/systemfonts/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c cpp11.cpp -o cpp11.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/svglite/systemfonts/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c devSVG.cpp -o devSVG.o
clang++ -arch arm64 -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o svglite.so cpp11.o devSVG.o -lpng -lz -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
...
** building package indices
** installing vignettes
** testing if installed package can be loaded from temporary location
Error: package or namespace load failed for ‘svglite’ in dyn.load(file, DLLpath = DLLpath, ...):
 unable to load shared object '/Users/romainfrancois/git/cpp11/revdep/checks.noindex/svglite/new/svglite.Rcheck/00LOCK-svglite/00new/svglite/libs/svglite.so':
  dlopen(/Users/romainfrancois/git/cpp11/revdep/checks.noindex/svglite/new/svglite.Rcheck/00LOCK-svglite/00new/svglite/libs/svglite.so, 0x0006): symbol not found in flat namespace '_png_create_info_struct'
Error: loading failed
Execution halted
ERROR: loading failed
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/svglite/new/svglite.Rcheck/svglite’


```
### CRAN

```
* installing *source* package ‘svglite’ ...
** package ‘svglite’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++11
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/svglite/systemfonts/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c cpp11.cpp -o cpp11.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/svglite/systemfonts/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c devSVG.cpp -o devSVG.o
clang++ -arch arm64 -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/lib -L/opt/R/arm64/lib -o svglite.so cpp11.o devSVG.o -lpng -lz -F/Library/Frameworks/R.framework/Versions/4.3-arm64 -framework R -Wl,-framework -Wl,CoreFoundation
...
** building package indices
** installing vignettes
** testing if installed package can be loaded from temporary location
Error: package or namespace load failed for ‘svglite’ in dyn.load(file, DLLpath = DLLpath, ...):
 unable to load shared object '/Users/romainfrancois/git/cpp11/revdep/checks.noindex/svglite/old/svglite.Rcheck/00LOCK-svglite/00new/svglite/libs/svglite.so':
  dlopen(/Users/romainfrancois/git/cpp11/revdep/checks.noindex/svglite/old/svglite.Rcheck/00LOCK-svglite/00new/svglite/libs/svglite.so, 0x0006): symbol not found in flat namespace '_png_create_info_struct'
Error: loading failed
Execution halted
ERROR: loading failed
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/svglite/old/svglite.Rcheck/svglite’


```
# vdiffr

<details>

* Version: 1.0.5
* GitHub: https://github.com/r-lib/vdiffr
* Source code: https://github.com/cran/vdiffr
* Date/Publication: 2023-01-23 14:40:02 UTC
* Number of recursive dependencies: 70

Run `revdepcheck::revdep_details(, "vdiffr")` for more info

</details>

## In both

*   checking whether package ‘vdiffr’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/vdiffr/new/vdiffr.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘vdiffr’ ...
** package ‘vdiffr’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++11
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c compare.cpp -o compare.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c cpp11.cpp -o cpp11.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/new/cpp11/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c devSVG.cpp -o devSVG.o
...
*** copying figures
** building package indices
** testing if installed package can be loaded from temporary location
Error: package or namespace load failed for ‘vdiffr’ in dyn.load(file, DLLpath = DLLpath, ...):
 unable to load shared object '/Users/romainfrancois/git/cpp11/revdep/checks.noindex/vdiffr/new/vdiffr.Rcheck/00LOCK-vdiffr/00new/vdiffr/libs/vdiffr.so':
  dlopen(/Users/romainfrancois/git/cpp11/revdep/checks.noindex/vdiffr/new/vdiffr.Rcheck/00LOCK-vdiffr/00new/vdiffr/libs/vdiffr.so, 0x0006): symbol not found in flat namespace '_png_create_info_struct'
Error: loading failed
Execution halted
ERROR: loading failed
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/vdiffr/new/vdiffr.Rcheck/vdiffr’


```
### CRAN

```
* installing *source* package ‘vdiffr’ ...
** package ‘vdiffr’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
using C++ compiler: ‘Apple clang version 14.0.3 (clang-1403.0.22.14.1)’
using C++11
using SDK: ‘MacOSX13.0.sdk’
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c compare.cpp -o compare.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c cpp11.cpp -o cpp11.o
clang++ -arch arm64 -std=gnu++11 -I"/Library/Frameworks/R.framework/Versions/4.3-arm64/Resources/include" -DNDEBUG  -I'/Users/romainfrancois/git/cpp11/revdep/library.noindex/cpp11/old/cpp11/include' -I/opt/R/arm64/include    -fPIC  -Wall -O3 -c devSVG.cpp -o devSVG.o
...
*** copying figures
** building package indices
** testing if installed package can be loaded from temporary location
Error: package or namespace load failed for ‘vdiffr’ in dyn.load(file, DLLpath = DLLpath, ...):
 unable to load shared object '/Users/romainfrancois/git/cpp11/revdep/checks.noindex/vdiffr/old/vdiffr.Rcheck/00LOCK-vdiffr/00new/vdiffr/libs/vdiffr.so':
  dlopen(/Users/romainfrancois/git/cpp11/revdep/checks.noindex/vdiffr/old/vdiffr.Rcheck/00LOCK-vdiffr/00new/vdiffr/libs/vdiffr.so, 0x0006): symbol not found in flat namespace '_png_create_info_struct'
Error: loading failed
Execution halted
ERROR: loading failed
* removing ‘/Users/romainfrancois/git/cpp11/revdep/checks.noindex/vdiffr/old/vdiffr.Rcheck/vdiffr’


```
