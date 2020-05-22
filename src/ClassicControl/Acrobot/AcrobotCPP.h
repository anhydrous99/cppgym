//
// Created by constexpr_dog on 5/17/20.
//

#ifndef CPPGYM_ACROBOT_H
#define CPPGYM_ACROBOT_H

#include "../ClassicEnvCPP.h"
#include <valarray>

class AcrobotCPP : public ClassicEnvCPP<float, int8_t, 6, 4> {
    std::uniform_real_distribution<float> dist{-0.1, 0.1};
    std::array<float, 6> get_obs();
    bool terminal();
    [[nodiscard]] std::valarray<float> dsdt(const std::valarray<float> &u) const;

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

    AcrobotCPP();
    std::tuple<std::array<float, 6>, float, bool> step(int8_t action) override;
    std::array<float, 6> reset() override;
    std::array<float, 4> raw_state();
};

#endif //CPPGYM_ACROBOT_H
