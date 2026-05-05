#include "cpp11/protect.hpp"

[[cpp11::register]] void test_template_warning() { cpp11::warning("%s", "warning"); }
