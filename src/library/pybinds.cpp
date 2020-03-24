/**
 * Created by mark on 2020-03-22.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#include "library.h"
#include "generated/thing1.hpp"
#include "generated/thing2.hpp"

PYBIND11_MODULE(generated_code_test, m) {
    m.def("hello", &hello);
    m.def("thing1", &thing1);
}
