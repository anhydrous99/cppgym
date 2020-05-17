cmake_minimum_required(VERSION 3.16)
project(cppgym)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(pybind11)

pybind11_add_module(_CartPole
        src/binder.cpp
        src/EnvCPP.h
        src/CartPoleCPP.h
        src/CartPoleCPP.cpp)
