//
// Created by constexpr_dog on 5/17/20.
//

#include "AcrobotCPP.h"
#include <functional>
#include <algorithm>
#include <cassert>
#include <tuple>

AcrobotCPP::AcrobotCPP() : EnvCPP<float, int8_t, 6>() {}

float wrap(float x, float m, float M) {
    float diff = M - m;
    while (x > M)
        x = x - diff;
    while (x < m)
        x = x + diff;
    return x;
}

float bound(float x, float m, float M) {
    return std::min(std::max(x, m), M);
}

std::tuple<std::array<float, 6>, float, bool> AcrobotCPP::step(int8_t action) {
    assert(0 <= action && action <= 3);
    float torque = avail_torque[action];

    // Add noise to the force action
    if (torque_noise_max > 0.0f) {
        std::uniform_real_distribution<float> tmp_dist(-torque_noise_max, torque_noise_max);
        torque += tmp_dist(_ran_generator);
    }
    const std::array<float, 5> s_augmented{ _state[0], _state[1], _state[2], _state[3],  torque};
    const std::array<float, 2> tspan{ 0.0f, dt };
    std::array<float, 2> t{ 0.0f };
    std::array<float, 5> y{ 0.0f };
    rk4([&](float t, const float u[], float f[]) { dsdt(t, u, f); },
            tspan.data(), s_augmented.data(), 1, 5, t.data(), y.data());
    std::array<float, 4> ns{y[0], y[1], y[2], y[3]};
    _state[0] = wrap(ns[0], -M_PIf32, M_PIf32);
    _state[1] = wrap(ns[1], -M_PIf32, M_PIf32);
    _state[2] = bound(ns[2], -max_vel_1, max_vel_1);
    _state[3] = bound(ns[3], -max_vel_2, max_vel_2);
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

void AcrobotCPP::dsdt(float t, const float u[], float f[]) const {
    //auto [theta1, theta2, dtheta1, dtheta2] = u;
    const float theta1 = u[0];
    const float theta2 = u[1];
    const float dtheta1 = u[2];
    const float dtheta2 = u[3];
    const float a = u[4];
    // Calculate the sine and cosine of theta1 and theta2
    float stheta1, ctheta1, stheta2, ctheta2;
    sincosf(theta1, &stheta1, &ctheta1);
    sincosf(theta2, &stheta2, &ctheta2);

    // Calculate d1
    const float d1 = I2 + mllp2lclc + mllc2 * ctheta2;
    const float d2 = I + mllc * ctheta2 + mlclc;
    const float phi2 = glcm * std::sin(theta1 + theta2);
    const float phi1 = gmlplc * stheta1 - mllc * dtheta2 * (2.0f * dtheta1 + dtheta2) * stheta2 + phi2;
    const float ddtheta2 = (d1 * (phi2 - a) - d2 * phi1 + mllc * d1 * dtheta1 * dtheta1 * stheta2) /
            (d2 * d2 - d1 * (mlclc + I));
    const float ddtheta1 = -(d2 * ddtheta2 + phi1) / d1;
    f[0] = dtheta1;
    f[1] = dtheta2;
    f[2] = ddtheta1;
    f[3] = ddtheta2;
    f[4] = 0.0f;
}
