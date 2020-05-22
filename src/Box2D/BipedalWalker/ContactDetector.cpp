//
// Created by constexpr_dog on 5/21/2020.
//

#include "ContactDetector.h"

ContactDetector::ContactDetector(BipedalWalkerCPP* env) : b2ContactListener() {
    this->env = env;
}

void ContactDetector::BeginContact(b2Contact *contact) {

}

void ContactDetector::EndContact(b2Contact *contact) {

}
