//
// Created by constexpr_dog on 5/18/20.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "AcrobotCPP.h"

namespace py = pybind11;

PYBIND11_MODULE(_Acrobot, m) {
    py::class_<AcrobotCPP>(m, "AcrobotCPP")
            .def(py::init())
            .def("set_seed", &AcrobotCPP::set_seed)
            .def("get_seed", &AcrobotCPP::get_seed)
            .def("step", &AcrobotCPP::step)
            .def("reset", &AcrobotCPP::reset)
            .def("raw_state", &AcrobotCPP::raw_state)
            .def_readonly("dt", &AcrobotCPP::dt)
            .def_readonly("link_length", &AcrobotCPP::link_length)
            .def_readonly("link_mass", &AcrobotCPP::link_mass)
            .def_readonly("link_com_pos", &AcrobotCPP::link_com_pos)
            .def_readonly("link_moi", &AcrobotCPP::link_moi)
            .def_readonly("max_vel_1", &AcrobotCPP::max_vel_1)
            .def_readonly("max_vel_2", &AcrobotCPP::max_vel_2)
            .def_readwrite("torque_noise_max", &AcrobotCPP::torque_noise_max);
}