//
// Created by constexpr_dog on 5/21/2020.
//

#ifndef CPPGYM_CONTACTDETECTOR_H
#define CPPGYM_CONTACTDETECTOR_H

#include <box2d/b2_world_callbacks.h>
#include "BiPedalWalkerCPP.h"

class ContactDetector : public b2ContactListener {
    BipedalWalkerCPP *env = nullptr;
public:
    explicit ContactDetector(BipedalWalkerCPP* env);
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
};


#endif //CPPGYM_CONTACTDETECTOR_H
