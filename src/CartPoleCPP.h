//
// Created by constexpr_dog on 5/16/20.
//

#ifndef CPPGYM_CARTPOLECPP_H
#define CPPGYM_CARTPOLECPP_H


#include "EnvCPP.h"
#include <tuple>

class CartPoleCPP : public EnvCPP<float, 4> {
    std::uniform_real_distribution<float> dist{-0.05, 0.05};
    int _steps_beyond_done = -1;
public:
    const float gravity = 9.8;
    const float masscart = 1.0;
    const float masspole = 0.1;
    const float total_mass = masspole + masscart;
    const float length = 0.5;
    const float polemass_length = masspole * length;
    const float force_mag = 10.0;
    const float tau = 0.02;
    const float x_threshold = 2.4;
    const float theta_threshold_radians = 12 * 2 * M_PI / 360;
    const float fourthirds = 4.0f / 3.0f;
    const float polemassfrac = masspole / total_mass;
    const float polemasslengthfrac = polemass_length / total_mass;

    CartPoleCPP();
    std::tuple<std::array<float, 4>, float, bool> step(int8_t action) override;
    std::array<float, 4> reset() override;
};



#endif //CPPGYM_CARTPOLECPP_H
