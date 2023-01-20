//
// Created by aaama on 17/01/2023.
//

#include "PositionComponent.h"

int PositionComponent::getX() const {
    return x;
}

void PositionComponent::setX(int x) {
    PositionComponent::x = x;
}

int PositionComponent::getY() const {
    return y;
}

void PositionComponent::setY(int y) {
    PositionComponent::y = y;
}
