//
// Created by constexpr_dog on 5/16/20.
//

#ifndef CPPGYM_MOUNTAINCARCPP_H
#define CPPGYM_MOUNTAINCARCPP_H

#include "../EnvCPP.h"

class MountainCarCPP : public EnvCPP<float, int8_t, 2> {
    std::uniform_real_distribution<float> dist{-0.6, -0.4};
public:
    const float min_position = -1.2;
    const float max_position = 0.6;
    const float max_speed = 0.07;
    const float goal_position = 0.5;
    float goal_velocity;
    const float force = 0.001;
    const float gravity = 0.0025;

    explicit MountainCarCPP(float goal_velocity);
    std::tuple<std::array<float, 2>, float, bool> step(int8_t action) override;
    std::array<float, 2> reset() override;
};

#endif //CPPGYM_MOUNTAINCARCPP_H
