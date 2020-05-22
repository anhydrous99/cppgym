//
// Created by constexpr_dog on 5/17/20.
//

#include <algorithm>
#include "PendulumCPP.h"

constexpr float pi2 = 2 * M_PIf32;
float angle_normalized(float x) {
    return x - pi2 * std::floor((x + M_PIf32) / pi2);
}

PendulumCPP::PendulumCPP(float g) : ClassicEnvCPP<float, float, 3, 2>() {
    this->g = g;
}

std::tuple<std::array<float, 3>, float, bool> PendulumCPP::step(float action) {
    auto& [th, thdot] = _state;

    action = std::clamp(action, -max_torque, max_torque);
    last_u = action;
    float costs = std::pow(angle_normalized(th), 2.0f) + 0.1f * thdot * thdot + 0.001f * action * action;

    thdot += (neg3gdev2l * std::sin(th + M_PIf32) + mlldiv3 * action) * dt;
    th += thdot * dt;
    thdot = std::clamp(thdot, -max_speed, max_speed);
    return std::make_tuple(get_obs(), -costs, false);
}

std::array<float, 3> PendulumCPP::reset() {
    _state[0] = dist1(_ran_generator);
    _state[1] = dist2(_ran_generator);
    last_u = 0;
    return get_obs();
}

std::array<float, 3> PendulumCPP::get_obs() {
    float s, c;
    sincosf(_state[0], &s, &c);
    return {c, s, _state[1]};
}