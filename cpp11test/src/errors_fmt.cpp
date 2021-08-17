#define CPP11_USE_FMT
#include "cpp11/function.hpp"
#include "cpp11/protect.hpp"
using namespace cpp11;

[[cpp11::register]] void my_stop(std::string mystring, int myarg) {
  cpp11::stop(mystring, myarg);
}
[[cpp11::register]] void my_stop_n1(std::string mystring) {
  cpp11::stop(mystring);
}
[[cpp11::register]] void my_warning(std::string mystring, std::string myarg) {
  cpp11::warning(mystring, myarg);
}
[[cpp11::register]] void my_warning_n1(std::string mystring) {
  cpp11::warning(mystring);
}
[[cpp11::register]] void my_message(std::string mystring, std::string myarg) {
  cpp11::message(mystring, myarg);
}
[[cpp11::register]] void my_message_n1(std::string mystring) {
  cpp11::message(mystring);
}
