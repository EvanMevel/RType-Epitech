//
// Created by aaama on 17/01/2023.
//

#include "HitboxComponent.h"

size_t HitboxComponent::getLengthX() const {
    return length_x;
}

size_t HitboxComponent::getLengthY() const {
    return length_y;
}

void HitboxComponent::setLengthY(size_t lengthY) {
    length_y = lengthY;
}

void HitboxComponent::setLengthX(size_t lengthX) {
    length_x = lengthX;
}
