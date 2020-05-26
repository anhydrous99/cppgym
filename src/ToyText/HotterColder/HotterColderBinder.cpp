//
// Created by constexpr_dog on 5/26/20.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "HotterColderCPP.h"

namespace py = pybind11;

PYBIND11_MODULE(_HotterColder, m) {
    py::class_<HotterColderCPP>(m, "HotterColderCPP")
            .def(py::init())
            .def("set_seed", &HotterColderCPP::set_seed)
            .def("get_seed", &HotterColderCPP::get_seed)
            .def("step", &HotterColderCPP::step)
            .def("reset", &HotterColderCPP::reset)
            .def_readonly("range", &HotterColderCPP::range)
            .def_readonly("bounds", &HotterColderCPP::bounds)
            .def_readonly("guess_max", &HotterColderCPP::guess_max);
}