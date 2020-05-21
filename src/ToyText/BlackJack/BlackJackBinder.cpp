//
// Created by constexpr_dog on 5/18/20.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "BlackJackCPP.h"

namespace py = pybind11;

PYBIND11_MODULE(_BlackJack, m) {
    py::class_<BlackJackCPP>(m, "BlackJackCPP")
            .def(py::init<bool>())
            .def("set_seed", &BlackJackCPP::set_seed)
            .def("get_seed", &BlackJackCPP::get_seed)
            .def("step", &BlackJackCPP::step)
            .def("reset", &BlackJackCPP::reset)
            .def_readwrite("natural", &BlackJackCPP::natural);
}