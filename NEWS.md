# cpp11 (development version)

* `writable::logicals::operator=()` now allows C++ boolean values (#57, @romainfrancois)

* `list::const_iterator::operator*()` added so iterators could be used on list objects (#60, @romainfrancois)

* `cpp11::as_cpp<int>()` and `cpp11::as_cpp<double>()` now implicitly coerce between all 3 types of single NA values (#53).

* The `END_CPP` macro now includes a `catch(...)` block to catch all C++ exceptions that do not inherit from `std::exception` (#47).

* Improve consistency of inserting NA values in r_string objects (#45)

* Added a `NEWS.md` file to track changes to the package.

# cpp11 0.1.0

* Initial release
