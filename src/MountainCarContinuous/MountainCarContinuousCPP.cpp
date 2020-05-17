//
// Created by constexpr_dog on 5/17/20.
//

#include <algorithm>
#include <tuple>
#include <cmath>
#include "MountainCarContinuousCPP.h"

MountainCarContinuousCPP::MountainCarContinuousCPP(float goal_velocity) : EnvCPP<float, float, 2>() {
    this->goal_velocity = goal_velocity;
}

std::tuple<std::array<float, 2>, float, bool> MountainCarContinuousCPP::step(float action) {
    auto& [position, velocity] = _state;
    float force = std::clamp(action, min_action, max_action);

    velocity += force * power - 0.0025 * std::cos(3 * position);
    velocity = std::clamp(velocity, -max_speed, max_speed);
    position += velocity;
    position = std::clamp(position, min_position, max_position);
    if (position == min_position && velocity < 0)
        velocity = 0;

    bool done = position >= goal_position && velocity >= goal_velocity;

    float reward = 0.0f;
    if (done)
        reward = 100.0f;
    reward -= action * action * 0.1f;
    return std::make_tuple(_state, reward, done);
}

std::array<float, 2> MountainCarContinuousCPP::reset() {
    _state[0] = dist(_ran_generator);
    _state[1] = 0;
    return _state;
}