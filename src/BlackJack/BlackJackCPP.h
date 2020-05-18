//
// Created by constexpr_dog on 5/18/20.
//

#ifndef CPPGYM_BLACKJACKCPP_H
#define CPPGYM_BLACKJACKCPP_H

#include "../EnvCPP.h"

class BlackJackCPP : public EnvCPP<int8_t, int8_t, 3> {
    std::array<int8_t, 13> deck;
    std::vector<int8_t> player;
    std::vector<int8_t> dealer;

    int8_t draw_card();
    std::vector<int8_t> draw_hand();
    static bool usable_ace(const std::vector<int8_t> &hand);
    static int8_t sum_hand(const std::vector<int8_t> &hand);
    static bool is_bust(const std::vector<int8_t> &hand);
    static int8_t score(const std::vector<int8_t> &hand);
    static bool is_natural(std::vector<int8_t> hand);
    std::array<int8_t, 3> get_obs();
public:
    bool natural;

    explicit BlackJackCPP(bool natural);
    std::tuple<std::array<int8_t, 3>, float, bool> step(int8_t action) override;
    std::array<int8_t, 3> reset() override;
};

#endif //CPPGYM_BLACKJACKCPP_H
