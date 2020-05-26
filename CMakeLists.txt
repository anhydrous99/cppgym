cmake_minimum_required(VERSION 3.16)
project(cppgym)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(extern/pybind11)

include(CheckCXXSymbolExists)
check_cxx_symbol_exists(sincosf "math.h" HAVE_SINCOSF)
if (HAVE_SINCOSF)
    add_definitions(-DHAVE_SINCOSF)
endif ()

pybind11_add_module(_CartPole
        src/EnvCPP.h
        src/EnvCPP.cpp
        src/ClassicControl/ClassicEnvCPP.h
        src/ClassicControl/CartPole/CartPoleBinder.cpp
        src/ClassicControl/CartPole/CartPoleCPP.h
        src/ClassicControl/CartPole/CartPoleCPP.cpp)

pybind11_add_module(_MountainCar
        src/EnvCPP.h
        src/EnvCPP.cpp
        src/ClassicControl/ClassicEnvCPP.h
        src/ClassicControl/MountainCar/MountainCarBinder.cpp
        src/ClassicControl/MountainCar/MountainCarCPP.h
        src/ClassicControl/MountainCar/MountainCarCPP.cpp)

pybind11_add_module(_MountainCarContinuous
        src/EnvCPP.h
        src/EnvCPP.cpp
        src/ClassicControl/ClassicEnvCPP.h
        src/ClassicControl/MountainCarContinuous/MountainCarContinuousBinder.cpp
        src/ClassicControl/MountainCarContinuous/MountainCarContinuousCPP.h
        src/ClassicControl/MountainCarContinuous/MountainCarContinuousCPP.cpp)

pybind11_add_module(_Pendulum
        src/EnvCPP.h
        src/EnvCPP.cpp
        src/ClassicControl/ClassicEnvCPP.h
        src/ClassicControl/Pendulum/PendulumBinder.cpp
        src/ClassicControl/Pendulum/PendulumCPP.h
        src/ClassicControl/Pendulum/PendulumCPP.cpp)

pybind11_add_module(_Acrobot
        src/EnvCPP.h
        src/EnvCPP.cpp
        src/ClassicControl/ClassicEnvCPP.h
        src/ClassicControl/Acrobot/ArcobotBinder.cpp
        src/ClassicControl/Acrobot/AcrobotCPP.h
        src/ClassicControl/Acrobot/AcrobotCPP.cpp)

pybind11_add_module(_BlackJack
        src/EnvCPP.h
        src/EnvCPP.cpp
        src/ToyText/BlackJack/BlackJackBinder.cpp
        src/ToyText/BlackJack/BlackJackCPP.h
        src/ToyText/BlackJack/BlackJackCPP.cpp)

pybind11_add_module(_HotterColder
        src/EnvCPP.h
        src/EnvCPP.cpp
        src/ToyText/HotterColder/HotterColderBinder.cpp
        src/ToyText/HotterColder/HotterColderCPP.h
        src/ToyText/HotterColder/HotterColderCPP.cpp)
