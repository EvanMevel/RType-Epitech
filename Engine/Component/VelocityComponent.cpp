//
// Created by aaama on 17/01/2023.
//

#include "VelocityComponent.h"

int VelocityComponent::getX() const {
    return x;
}

void VelocityComponent::setX(int x) {
    VelocityComponent::x = x;
}

int VelocityComponent::getY() const {
    return y;
}

void VelocityComponent::setY(int y) {
    VelocityComponent::y = y;
}
