//
// Created by constexpr_dog on 5/16/20.
//

#ifndef CPPGYM_ENVCPP_H
#define CPPGYM_ENVCPP_H

#include <array>
#include <cmath>
#include <random>
#include <cstdint>

#ifndef M_PIf32
#define M_PIf32 3.14159265358979323846
#endif

#ifndef HAVE_SINCOSF
inline void sincosf(float xx, float *s, float *c) {
  *s = std::sin(xx);
  *c = std::cos(xx);
}
#endif

template <typename StateType, typename ActionType, int StateSize>
class EnvCPP {
protected:
    std::mt19937 _ran_generator;
    std::array<StateType, StateSize> _state{0};
    uint32_t _seed;

public:
    EnvCPP();
    void set_seed(uint32_t seed);
    uint32_t get_seed();
    virtual std::tuple<std::array<StateType, StateSize>, float, bool> step(ActionType action) = 0;
    virtual std::array<StateType, StateSize> reset() = 0;
};

// -- Implementation --

template <typename StateType, typename ActionType, int StateSize>
EnvCPP<StateType, ActionType, StateSize>::EnvCPP() : _seed((std::random_device())()) {
    _ran_generator = std::mt19937(_seed);
}

template <typename StateType, typename ActionType, int StateSize>
void EnvCPP<StateType, ActionType, StateSize>::set_seed(uint32_t seed) {
    _ran_generator = std::mt19937(seed);
}

template <typename StateType, typename ActionType, int StateSize>
uint32_t EnvCPP<StateType, ActionType, StateSize>::get_seed() {
    return _seed;
}

#endif //CPPGYM_ENVCPP_H
