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

[[cpp11::register]] void my_stop_n1fmt(std::string mystring) { cpp11::stop(mystring); }
[[cpp11::register]] void my_stop_n2fmt(std::string mystring, std::string myarg) {
  cpp11::stop(mystring, myarg.c_str());
}
[[cpp11::register]] void my_warning_n1fmt(std::string mystring) {
  cpp11::warning(mystring);
}
[[cpp11::register]] void my_warning_n2fmt(std::string mystring, std::string myarg) {
  cpp11::warning(mystring, myarg.c_str());
}
<<<<<<< HEAD
<<<<<<< HEAD

[[cpp11::register]] void my_message_nfmt(std::string mystring, std::string myarg) {
  cpp11::message(mystring, myarg.c_str());
}
=======
>>>>>>> upstream/master
=======
[[cpp11::register]] void my_message_nfmt(std::string mystring, std::string myarg) {
  cpp11::message(mystring, myarg.c_str());
}
>>>>>>> 3b3ff2861878876c2a942808846b172209a28ab7
