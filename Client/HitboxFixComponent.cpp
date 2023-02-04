//
// Created by audre on 02/02/2023.
//

#include "HitboxFixComponent.h"

const Hitbox &HitboxFixComponent::getHitbox() const {
    return hitbox;
}

void HitboxFixComponent::setHitbox(const Hitbox &hitbox) {
    this->hitbox = hitbox;
}

HitboxFixComponent::HitboxFixComponent() {

}
