//
// Created by constexpr_dog on 5/16/20.
//

#ifndef CPPGYM_CLASSICENVCPP_H
#define CPPGYM_CLASSICENVCPP_H

#include "../EnvCPP.h"
#include <array>

template <typename StateType, typename ActionType, int ObsStateSize, int IntStateSize=ObsStateSize>
class ClassicEnvCPP : public EnvCPP {
protected:
    std::array<StateType, IntStateSize> _state{0};

public:
    ClassicEnvCPP();
    virtual std::tuple<std::array<StateType, ObsStateSize>, float, bool> step(ActionType action) = 0;
    virtual std::array<StateType, ObsStateSize> reset() = 0;
};

// -- Implementation --

template <typename StateType, typename ActionType, int StateSize, int IntStateSize>
ClassicEnvCPP<StateType, ActionType, StateSize, IntStateSize>::ClassicEnvCPP() : EnvCPP() {}

#endif //CPPGYM_CLASSICENVCPP_H
