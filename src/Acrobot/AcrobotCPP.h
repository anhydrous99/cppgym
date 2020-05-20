//
// Created by constexpr_dog on 5/17/20.
//

#ifndef CPPGYM_ACROBOT_H
#define CPPGYM_ACROBOT_H

#include "../EnvCPP.h"
#include <functional>

class AcrobotCPP : public EnvCPP<float, int8_t, 6> {
    std::uniform_real_distribution<float> dist{-0.1, 0.1};
    std::array<float, 6> get_obs();
    bool terminal();
    void dsdt(float t, const float u[], float f[]) const;

public:
    const float dt = 0.2f;
    const float link_length = 1.0f;
    const float link_mass = 1.0f;
    const float link_com_pos = 0.5f;
    const float link_moi = 1.0f;
    const float max_vel_1 = 4.0f * M_PIf32;
    const float max_vel_2 = 9.0f * M_PIf32;
    const std::array<float, 3> avail_torque{-1.0f, 0.0f, 1.0f};
    float torque_noise_max = 0.0f;
    const bool book_or_nips = true; // set to false for nips

    // Precalculations
    const float m = link_mass;
    const float l = link_length;
    const float lc = link_com_pos;
    const float I = link_moi;
    const float g = 9.8f;
    const float ll = l * l;
    const float lclc = lc * lc;
    const float mlclc = m * lclc;
    const float llc = l * lc;
    const float mllc = m * llc;
    const float llc2 = llc * 2.0f;
    const float mllc2 = llc2 * m;
    const float lclc2 = lclc * 2.0f;
    const float I2 = I * 2.0f;
    const float glcm = g * lc * m;
    const float gmlplc = g * m * (l + lc);
    const float mllp2lclc = m * (ll + lclc2);

    AcrobotCPP();
    std::tuple<std::array<float, 6>, float, bool> step(int8_t action) override;
    std::array<float, 6> reset() override;

};

#endif //CPPGYM_ACROBOT_H
