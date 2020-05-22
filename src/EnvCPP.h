//
// Created by bsq699 on 5/21/2020.
//

#ifndef CPPGYM_ENVCPP_H
#define CPPGYM_ENVCPP_H

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

class EnvCPP {
protected:
    uint32_t _seed;
    std::mt19937 _ran_generator;

public:
    EnvCPP();
    void set_seed(uint32_t seed);
    uint32_t get_seed();
};

#endif //CPPGYM_ENVCPP_H
