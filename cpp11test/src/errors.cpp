#include "cpp11/protect.hpp"
using namespace cpp11;

[[cpp11::register]] void my_stop(std::string mystring, int myarg) {
  cpp11::stop(mystring, myarg);
}

[[cpp11::register]] void my_warning(std::string mystring, std::string myarg) {
  cpp11::warning(mystring, myarg);
}
