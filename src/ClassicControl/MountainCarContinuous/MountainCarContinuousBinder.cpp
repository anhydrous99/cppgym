//
// Created by constexpr_dog on 5/17/20.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "MountainCarContinuousCPP.h"

namespace py = pybind11;

PYBIND11_MODULE(_MountainCarContinuous, m) {
    py::class_<MountainCarContinuousCPP>(m, "MountainCarContinuousCPP")
            .def(py::init<float>())
            .def("set_seed", &MountainCarContinuousCPP::set_seed)
            .def("get_seed", &MountainCarContinuousCPP::get_seed)
            .def("step", &MountainCarContinuousCPP::step)
            .def("reset", &MountainCarContinuousCPP::reset)
            .def_readonly("min_action", &MountainCarContinuousCPP::min_action)
            .def_readonly("max_action", &MountainCarContinuousCPP::max_action)
            .def_readonly("min_position", &MountainCarContinuousCPP::min_position)
            .def_readonly("max_position", &MountainCarContinuousCPP::max_position)
            .def_readonly("max_speed", &MountainCarContinuousCPP::max_speed)
            .def_readonly("goal_position", &MountainCarContinuousCPP::goal_position)
            .def_readwrite("goal_velocity", &MountainCarContinuousCPP::goal_velocity)
            .def_readonly("power", &MountainCarContinuousCPP::power);
}