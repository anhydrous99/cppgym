//
// Created by constexpr_dog on 5/17/20.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "PendulumCPP.h"

namespace py = pybind11;

PYBIND11_MODULE(_Pendulum, m) {
    py::class_<PendulumCPP>(m, "PendulumCPP")
            .def(py::init<float>())
            .def("set_seed", &PendulumCPP::set_seed)
            .def("get_seed", &PendulumCPP::get_seed)
            .def("step", &PendulumCPP::step)
            .def("reset", &PendulumCPP::reset)
            .def_readonly("max_speed", &PendulumCPP::max_speed)
            .def_readonly("max_torque", &PendulumCPP::max_torque)
            .def_readonly("dt", &PendulumCPP::dt)
            .def_readwrite("g", &PendulumCPP::g)
            .def_readonly("m", &PendulumCPP::m)
            .def_readonly("l", &PendulumCPP::l)
            .def_readwrite("last_u", &PendulumCPP::last_u);
}