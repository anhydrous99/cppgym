//
// Created by constexpr_dog on 5/16/20.
//

#include <algorithm>
#include <cassert>
#include <tuple>
#include "MountainCarCPP.h"

MountainCarCPP::MountainCarCPP(float goal_velocity) : ClassicEnvCPP<float, int8_t, 2>() {
    this->goal_velocity = goal_velocity;
}

std::tuple<std::array<float, 2>, float, bool> MountainCarCPP::step(int8_t action) {
    assert(action == 0 || action == 1 || action == 2);

    auto& [position, velocity] = _state;
    velocity += (static_cast<float>(action) - 1.0f) * force - std::cos(3.0f * position) * (gravity);
    velocity = std::clamp(velocity, -max_speed, max_speed);
    position += velocity;
    position = std::clamp(position, min_position, max_position);
    if (position == min_position && velocity < 0)
        velocity = 0;

    bool done = position >= goal_position && velocity >= goal_velocity;
    float reward = -1.0f;
    return std::make_tuple(_state, reward, done);
}

std::array<float, 2> MountainCarCPP::reset() {
    _state[0] = dist(_ran_generator);
    _state[1] = 0;
    return _state;
}
