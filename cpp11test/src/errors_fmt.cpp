#define CPP11_USE_FMT
#include "cpp11/protect.hpp"
<<<<<<< HEAD
<<<<<<< HEAD
#include "cpp11/function.hpp"
=======
>>>>>>> upstream/master
=======
#include "cpp11/function.hpp"
>>>>>>> 3b3ff2861878876c2a942808846b172209a28ab7
using namespace cpp11;

[[cpp11::register]] void my_stop(std::string mystring, int myarg) {
  cpp11::stop(mystring, myarg);
}
[[cpp11::register]] void my_warning(std::string mystring, std::string myarg) {
  cpp11::warning(mystring, myarg);
}
<<<<<<< HEAD
<<<<<<< HEAD
[[cpp11::register]] void my_message(std::string mystring, std::string myarg) {
  cpp11::message(mystring, myarg);
}
=======
>>>>>>> upstream/master
=======
[[cpp11::register]] void my_message(std::string mystring, std::string myarg) {
  cpp11::message(mystring, myarg);
}
>>>>>>> 3b3ff2861878876c2a942808846b172209a28ab7
