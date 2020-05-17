//
// Created by constexpr_dog on 5/16/20.
//

#ifndef CPPGYM_ENVCPP_H
#define CPPGYM_ENVCPP_H

#include <array>
#include <random>
#include <cstdint>

template <typename T, int N>
class EnvCPP {
protected:
    std::mt19937 _ran_generator;
    std::array<T, N> _state{0};
    uint32_t _seed;

public:
    EnvCPP();
    void set_seed(uint32_t seed);
    uint32_t get_seed();
    virtual std::tuple<std::array<T, N>, T, bool> step(int8_t action) = 0;
    virtual std::array<T, N> reset() = 0;
};

// -- Implementation --

template <typename T, int N>
EnvCPP<T, N>::EnvCPP() : _seed((std::random_device())()) {
    _ran_generator = std::mt19937(_seed);
}

template <typename T, int N>
void EnvCPP<T, N>::set_seed(uint32_t seed) {
    _ran_generator = std::mt19937(seed);
}

template <typename T, int N>
uint32_t EnvCPP<T, N>::get_seed() {
    return _seed;
}

#endif //CPPGYM_ENVCPP_H
