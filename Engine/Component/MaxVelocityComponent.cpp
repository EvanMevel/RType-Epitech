//
// Created by evans on 28/01/2023.
//

#include "MaxVelocityComponent.h"

MaxVelocityComponent::MaxVelocityComponent(size_t maxVelocity) : maxVelocity(maxVelocity) {}

MaxVelocityComponent::MaxVelocityComponent() {}

size_t MaxVelocityComponent::getMaxVelocity() const {
    return maxVelocity;
}

void MaxVelocityComponent::setMaxVelocity(size_t maxVelocity) {
    MaxVelocityComponent::maxVelocity = maxVelocity;
}
