//
// Created by constexpr_dog on 5/26/20.
//

#ifndef CPPGYM_HOTTERCOLDERCPP_H
#define CPPGYM_HOTTERCOLDERCPP_H

#include "../../EnvCPP.h"
#include <map>
#include <string>
#include <cstdint>

class HotterColderCPP : public EnvCPP {
    float number = 0;
    int32_t guess_count = 0;
    int32_t observation = 0;
    std::uniform_real_distribution<float> dist{-range, range};

public:
    const float range = 1000;
    const float bounds = 2000;
    const float guess_max = 200;

    HotterColderCPP();
    std::tuple<int32_t, float, bool, std::map<std::string, int32_t>> step(float action);
    int32_t reset();
};

#endif //CPPGYM_HOTTERCOLDERCPP_H
