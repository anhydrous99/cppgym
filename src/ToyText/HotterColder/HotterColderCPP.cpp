//
// Created by constexpr_dog on 5/26/20.
//

#include "HotterColderCPP.h"
#include <algorithm>

HotterColderCPP::HotterColderCPP() = default;

std::tuple<int32_t, float, bool, std::map<std::string, int32_t>> HotterColderCPP::step(float action) {
    if (action < number)
        observation = 1;
    else if (action == number)
        observation = 2;
    else
        observation = 3;

    float reward = std::pow((std::min(action, number) + bounds) / (std::max(action, number) + bounds), 2.0f);

    guess_count++;
    bool done = guess_count >= guess_max;
    return {observation, reward, done, {{"number", number}, {"guesses", guess_count}}};
}

int32_t HotterColderCPP::reset() {
    number = dist(_ran_generator);
    guess_count = 0;
    observation = 0;
    return observation;
}
