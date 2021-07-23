#define CPP11_USE_FMT
#include "cpp11/protect.hpp"
<<<<<<< HEAD
#include "cpp11/function.hpp"
=======
>>>>>>> upstream/master
using namespace cpp11;

[[cpp11::register]] void my_stop(std::string mystring, int myarg) {
  cpp11::stop(mystring, myarg);
}
[[cpp11::register]] void my_warning(std::string mystring, std::string myarg) {
  cpp11::warning(mystring, myarg);
}
<<<<<<< HEAD
[[cpp11::register]] void my_message(std::string mystring, std::string myarg) {
  cpp11::message(mystring, myarg);
}
=======
>>>>>>> upstream/master
