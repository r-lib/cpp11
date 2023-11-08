#include "headers/function.hpp"
#include "headers/protect.hpp"
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
[[cpp11::register]] void my_message_n1fmt(std::string mystring) {
  cpp11::message(mystring);
}
[[cpp11::register]] void my_message_n2fmt(std::string mystring, std::string myarg) {
  cpp11::message(mystring, myarg.c_str());
}
