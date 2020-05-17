//
// Created by constexpr_dog on 5/16/20.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "MountainCarCPP.h"

namespace py = pybind11;

PYBIND11_MODULE(_MountainCar, m) {
    py::class_<MountainCarCPP>(m, "MountainCarCPP")
            .def(py::init<float>())
            .def("set_seed", &MountainCarCPP::set_seed)
            .def("get_seed", &MountainCarCPP::get_seed)
            .def("step", &MountainCarCPP::step)
            .def("reset", &MountainCarCPP::reset)
            .def_readonly("min_position", &MountainCarCPP::min_position)
            .def_readonly("max_position", &MountainCarCPP::max_position)
            .def_readonly("max_speed", &MountainCarCPP::max_speed)
            .def_readonly("goal_position", &MountainCarCPP::goal_position)
            .def_readwrite("goal_velocity", &MountainCarCPP::goal_velocity)
            .def_readonly("force", &MountainCarCPP::force)
            .def_readonly("gravity", &MountainCarCPP::gravity);
}