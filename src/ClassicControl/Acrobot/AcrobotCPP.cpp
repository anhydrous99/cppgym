//
// Created by constexpr_dog on 5/17/20.
//

#include "AcrobotCPP.h"
#include <functional>
#include <algorithm>
#include <cassert>
#include <tuple>

AcrobotCPP::AcrobotCPP() : EnvCPP<float, int8_t, 6, 4>() {}

float wrap(float x, float m, float M) {
    float diff = M - m;
    while (x > M)
        x -= diff;
    while (x < m)
        x += diff;
    return x;
}

std::tuple<std::array<float, 6>, float, bool> AcrobotCPP::step(int8_t action) {
    assert(0 <= action && action <= 3);
    float torque = avail_torque[action];

    // Add noise to the force action
    if (torque_noise_max > 0.0f) {
        std::uniform_real_distribution<float> tmp_dist(-torque_noise_max, torque_noise_max);
        torque += tmp_dist(_ran_generator);
    }

    // RK4 - single step
    const std::valarray<float> y0{_state[0], _state[1], _state[2], _state[3], torque};
    const float dt2 = dt / 2.0f;
    std::valarray<float> k1 = dsdt(y0);
    std::valarray<float> k2 = dsdt(y0 + dt2 * k1);
    std::valarray<float> k3 = dsdt(y0 + dt2 * k2);
    std::valarray<float> k4 = dsdt(y0 + dt * k3);
    std::valarray<float> y = y0 + dt / 6.0 * (k1 + 2 * k2 + 2 * k3 + k4);

    _state[0] = wrap(y[0], -M_PIf32, M_PIf32);
    _state[1] = wrap(y[1], -M_PIf32, M_PIf32);
    _state[2] = std::clamp(y[2], -max_vel_1, max_vel_1);
    _state[3] = std::clamp(y[3], -max_vel_2, max_vel_2);
    bool term = terminal();
    float reward = (!term) ? -1.0f : 0.0f;
    return std::make_tuple(get_obs(), reward, term);
}

std::array<float, 6> AcrobotCPP::reset() {
    std::generate(_state.begin(), _state.end(), [&](){ return dist(_ran_generator); });
    return get_obs();
}

std::array<float, 6> AcrobotCPP::get_obs() {
    float s0cos, s0sin, s1cos, s1sin;
    sincosf(_state[0], &s0sin, &s0cos);
    sincosf(_state[1], &s1sin, &s1cos);
    return {s0cos, s0sin, s1cos, s1sin, _state[2], _state[3]};
}

bool AcrobotCPP::terminal() {
    return ((-std::cos(_state[0]) - std::cos(_state[1] + _state[0])) > 1.0f);
}

std::valarray<float> AcrobotCPP::dsdt(const std::valarray<float> &u) const {
    const float theta1 = u[0];
    const float theta2 = u[1];
    const float dtheta1 = u[2];
    const float dtheta2 = u[3];
    const float a = u[4];

    const float d1 = m * lc * lc + m * (l * l + lc * lc + 2 * l * lc * std::cos(theta2)) + 2 * I;
    const float d2 = m * (lc * lc + l * lc * std::cos(theta2)) + I;
    const float phi2 = m * lc * g * std::cos(theta1 + theta2 - M_PIf32 / 2.0f);
    const float phi1 = - m * l * lc * dtheta2 * dtheta2 * std::sin(theta2) - 2 * m * l * lc * dtheta2 * dtheta1 *
            std::sin(theta2) + (m * lc + m * l) * g * std::cos(theta1 - M_PIf32 / 2.0f) + phi2;
    const float ddtheta2 = (a + d2 / d1 * phi1 - m * l * lc * dtheta1 * dtheta1 * std::sin(theta2) - phi2) /
            (m * lc * lc + I - d2 * d2 / d1);
    const float ddtheta1 = -(d2 * ddtheta2 + phi1) / d1;
    return {dtheta1, dtheta2, ddtheta1, ddtheta2, 0.0f};
}

std::array<float, 4> AcrobotCPP::raw_state() {
    return _state;
}
