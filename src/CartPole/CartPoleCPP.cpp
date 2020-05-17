//
// Created by constexpr_dog on 5/16/20.
//

#include "CartPoleCPP.h"
#include <algorithm>
#include <cassert>
#include <cmath>

CartPoleCPP::CartPoleCPP() : EnvCPP<float, int8_t, 4>() {}

std::tuple<std::array<float, 4>, float, bool> CartPoleCPP::step(int8_t action) {
    assert(action == -1 || action == 1);

    auto& [x, x_dot, theta, theta_dot] = _state;
    float force = (action == 1) ? force_mag : -force_mag;
    float costheta, sintheta;
    sincosf(theta, &sintheta, &costheta);

    float temp = (force + polemass_length * theta_dot * theta_dot * sintheta) / total_mass;
    float thetaacc = (gravity * sintheta - costheta * temp) / (length * (fourthirds - polemassfrac * costheta * costheta));
    float xacc = temp - polemasslengthfrac * thetaacc * costheta;

    x = x + tau * x_dot;
    x_dot = x_dot + tau * xacc;
    theta = theta + tau * theta_dot;
    theta_dot = theta_dot + tau * thetaacc;

    bool done = x < -x_threshold || x > x_threshold || theta < -theta_threshold_radians ||
                theta > theta_threshold_radians;

    float reward;
    if(!done)
        reward = 1.0f;
    else if (_steps_beyond_done == -1) {
        _steps_beyond_done = 0;
        reward = 1.0f;
    } else {
        _steps_beyond_done++;
        reward = 0.0f;
    }
    return std::make_tuple(_state, reward, done);
}

std::array<float, 4> CartPoleCPP::reset() {
    std::generate(_state.begin(), _state.end(), [&]() { return dist(_ran_generator); });
    _steps_beyond_done = -1;
    return _state;
}
