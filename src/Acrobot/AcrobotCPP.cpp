//
// Created by constexpr_dog on 5/17/20.
//

#include "AcrobotCPP.h"
#include <functional>
#include <algorithm>
#include <cassert>
#include <tuple>

AcrobotCPP::AcrobotCPP() : EnvCPP<float, int8_t, 6>() {}

std::tuple<std::array<float, 6>, float, bool> AcrobotCPP::step(int8_t action) {
    assert(0 <= action && action <= 3);
    float torque = avail_torque[action];

    // Add noise to the force action
    if (torque_noise_max > 0.0f) {
        std::uniform_real_distribution<float> tmp_dist(-torque_noise_max, torque_noise_max);
        torque += tmp_dist(_ran_generator);
    }
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

std::valarray<float> AcrobotCPP::dsdt(const std::array<float, 4> &s, float a) {
    auto [theta1, theta2, dtheta1, dtheta2] = s;

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
    return {dtheta1, dtheta2, ddtheta1, ddtheta2, 0.0f};
}

void AcrobotCPP::calc_rk4(const std::array<float, 5> &y0, const std::array<float, 2> &t) {
    
}