//
// Created by constexpr_dog on 5/17/20.
//

#ifndef CPPGYM_MOUNTAINCARCONTINUOUS_H
#define CPPGYM_MOUNTAINCARCONTINUOUS_H

#include "../ClassicEnvCPP.h"

class MountainCarContinuousCPP : public ClassicEnvCPP<float, float, 2> {
    std::uniform_real_distribution<float> dist{-0.6, -0.4};
public:
    const float min_action = -1.0;
    const float max_action = 1.0;
    const float min_position = -1.2;
    const float max_position = 0.6;
    const float max_speed = 0.07;
    const float goal_position = 0.45;
    float goal_velocity;
    const float power = 0.0015;

    explicit MountainCarContinuousCPP(float goal_velocity);
    std::tuple<std::array<float, 2>, float, bool> step(float action) override;
    std::array<float, 2> reset() override;
};

#endif //CPPGYM_MOUNTAINCARCONTINUOUS_H
