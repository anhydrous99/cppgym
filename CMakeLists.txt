cmake_minimum_required(VERSION 3.16)
project(cppgym)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(pybind11)

include(CheckCXXSymbolExists)
check_cxx_symbol_exists(sincosf "math.h" HAVE_SINCOSF)
if (HAVE_SINCOSF)
    add_definitions(-DHAVE_SINCOSF)
endif ()

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

pybind11_add_module(_Pendulum
        src/EnvCPP.h
        src/Pendulum/PendulumBinder.cpp
        src/Pendulum/PendulumCPP.h
        src/Pendulum/PendulumCPP.cpp)

pybind11_add_module(_Acrobot
        src/EnvCPP.h
        src/Acrobot/ArcobotBinder.cpp
        src/Acrobot/AcrobotCPP.h
        src/Acrobot/AcrobotCPP.cpp
        src/Acrobot/rk4.cpp)

pybind11_add_module(_BlackJack
        src/EnvCPP.h
        src/BlackJack/BlackJackBinder.cpp
        src/BlackJack/BlackJackCPP.h
        src/BlackJack/BlackJackCPP.cpp)