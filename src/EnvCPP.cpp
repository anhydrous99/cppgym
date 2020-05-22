//
// Created by bsq699 on 5/21/2020.
//

#include "EnvCPP.h"

EnvCPP::EnvCPP() : _seed((std::random_device())()) {}

void EnvCPP::set_seed(uint32_t seed) {
    _seed = seed;
    _ran_generator = std::mt19937(seed);
}

uint32_t EnvCPP::get_seed() {
    return _seed;
}
