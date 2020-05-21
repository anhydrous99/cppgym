//
// Created by constexpr_dog on 5/17/20.
//

#ifndef CPPGYM_PENDULUMCPP_H
#define CPPGYM_PENDULUMCPP_H

#include "../EnvCPP.h"

class PendulumCPP : public EnvCPP<float, float, 3, 2> {
    std::uniform_real_distribution<float> dist1{-M_PIf32, M_PIf32};
    std::uniform_real_distribution<float> dist2{-1, 1};

    std::array<float, 3> get_obs();
public:
    const float max_speed = 8.0f;
    const float max_torque = 2.0f;
    const float dt = 0.05f;
    float g = 10.0f;
    const float m = 1.0f;
    const float l = 1.0f;
    float last_u = 0.0f;
    const float neg3gdev2l = -3.f * g / (2 * l);
    const float mlldiv3 = 3.f / (m * l * l);

    explicit PendulumCPP(float g);
    std::tuple<std::array<float, 3>, float, bool> step(float action) override;
    std::array<float, 3> reset() override;
};

#endif //CPPGYM_PENDULUMCPP_H
