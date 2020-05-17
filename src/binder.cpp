//
// Created by constexpr_dog on 5/16/20.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "CartPoleCPP.h"

namespace py = pybind11;

PYBIND11_MODULE(_CartPole, m) {
    py::class_<CartPoleCPP>(m, "CartPoleCPP")
            .def(py::init())
            .def("set_seed", &CartPoleCPP::set_seed)
            .def("get_seed", &CartPoleCPP::get_seed)
            .def("step", &CartPoleCPP::step)
            .def("reset", &CartPoleCPP::reset)
            .def_readonly("gravity", &CartPoleCPP::gravity)
            .def_readonly("masscart", &CartPoleCPP::masscart)
            .def_readonly("masspole", &CartPoleCPP::masspole)
            .def_readonly("total_mass", &CartPoleCPP::total_mass)
            .def_readonly("length", &CartPoleCPP::length)
            .def_readonly("polemass_length", &CartPoleCPP::polemass_length)
            .def_readonly("force_mag", &CartPoleCPP::force_mag)
            .def_readonly("tau", &CartPoleCPP::tau)
            .def_readonly("x_threshold", &CartPoleCPP::x_threshold)
            .def_readonly("theta_threshold_radians", &CartPoleCPP::theta_threshold_radians);
}
