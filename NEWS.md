# cpp11 (development version)

* `cpp_source()`, `cpp_function()` and `cpp_eval()` now support `[[cpp11::linking_to()]]` syntax to link to third party packages with C++ headers. (#48)

* `safe[]` can now work with functions that return any type (#70, @bkietz)

* cpp11 is now able to compile on gcc 4.8.5 (#69, @bkietz)

* `as_cpp<E>()` now allows enumeration `E` (#52, @bkietz)

* `writable::logicals::operator=()` now allows C++ boolean values (#57, @romainfrancois)

* `list::const_iterator::operator*()` added so iterators could be used on list objects (#60, @romainfrancois)

* `cpp11::as_cpp<int>()` and `cpp11::as_cpp<double>()` now implicitly coerce between all 3 types of single NA values (#53).

* The `END_CPP` macro now includes a `catch(...)` block to catch all C++ exceptions that do not inherit from `std::exception` (#47).

* Improve consistency of inserting NA values in r_string objects (#45)

* Added a `NEWS.md` file to track changes to the package.

# cpp11 0.1.0

* Initial release
