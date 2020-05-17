cmake_minimum_required(VERSION 3.16)
project(cppgym)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(pybind11)

pybind11_add_module(_CartPole
        src/EnvCPP.h
        src/CartPole/CartPoleBinder.cpp
        src/CartPole/CartPoleCPP.h
        src/CartPole/CartPoleCPP.cpp)

pybind11_add_module(_MountainCar
        src/EnvCPP.h
        src/MountainCar/MountainCarBinder.cpp
        src/MountainCar/MountainCarCPP.h
        src/MountainCar/MountainCarCPP.cpp)

pybind11_add_module(_MountainCarContinuous
        src/EnvCPP.h
        src/MountainCarContinuous/MountainCarContinuousBinder.cpp
        src/MountainCarContinuous/MountainCarContinuousCPP.h
        src/MountainCarContinuous/MountainCarContinuousCPP.cpp)
