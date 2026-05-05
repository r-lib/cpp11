#include "cpp11/protect.hpp"

[[cpp11::register]] void test_template_stop() { cpp11::stop("%s", "stop"); }
