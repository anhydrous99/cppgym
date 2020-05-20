//
// Created by constexpr_dog on 5/18/20.
//

#include "BlackJackCPP.h"
#include <algorithm>

static float cmp(int8_t a, int8_t b) {
    return static_cast<float>(a > b) - static_cast<float>(a < b);
}

BlackJackCPP::BlackJackCPP(bool natural) : EnvCPP<int8_t, int8_t, 3, 1>(),
        deck{1, 2, 3, 4, 5,
             6, 7, 8, 9, 10,
             10, 10, 10},
             natural(natural)
        {}

int8_t BlackJackCPP::draw_card() {
    std::uniform_int_distribution<int8_t> distribution(0, deck.size() - 1);
    return deck[distribution(_ran_generator)];
}

std::vector<int8_t> BlackJackCPP::draw_hand() {
    return {draw_card(), draw_card()};
}

bool BlackJackCPP::usable_ace(const std::vector<int8_t> &hand) {
    auto begin = hand.begin();
    auto end = hand.end();
    return std::find(begin, end, 1) != end && std::accumulate(begin, end, 10) <= 21;
}

int8_t BlackJackCPP::sum_hand(const std::vector<int8_t> &hand) {
    if (usable_ace(hand))
        return std::accumulate(hand.begin(), hand.end(), 10);
    return std::accumulate(hand.begin(), hand.end(), 0);
}

bool BlackJackCPP::is_bust(const std::vector<int8_t> &hand) {
    return sum_hand(hand) > 21;
}

int8_t BlackJackCPP::score(const std::vector<int8_t> &hand) {
    return (is_bust(hand)) ? 0 : sum_hand(hand);
}

bool BlackJackCPP::is_natural(std::vector<int8_t> hand) {
    if (hand.size() != 2)
        return false;
    else {
        std::sort(hand.begin(), hand.end());
        return hand[0] == 1 && hand[1] == 10;
    }
}

std::array<int8_t, 3> BlackJackCPP::get_obs() {
    return {sum_hand(player), dealer[0], usable_ace(player)};
}

std::tuple<std::array<int8_t, 3>, float, bool> BlackJackCPP::step(int8_t action) {
    bool done;
    float reward;
    if (action) {
        player.push_back(draw_card());
        if (is_bust(player)) {
            done = true;
            reward = -1.0f;
        } else {
            done = false;
            reward = 0.0f;
        }
    } else {
        done = true;
        while (sum_hand(dealer) < 17)
            dealer.push_back(draw_card());
        reward = cmp(score(player), score(player));
        if (natural && is_natural(player) && reward == 1.0f)
            reward = 1.5f;
    }
    return std::make_tuple(get_obs(), reward, done);
}

std::array<int8_t, 3> BlackJackCPP::reset() {
    dealer = draw_hand();
    player = draw_hand();
    return get_obs();
}