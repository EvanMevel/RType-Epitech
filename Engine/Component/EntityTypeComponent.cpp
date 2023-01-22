//
// Created by aaama on 17/01/2023.
//

#include "EntityTypeComponent.h"

EntityType EntityTypeComponent::getType() const {
    return type;
}

void EntityTypeComponent::setType(EntityType type) {
    EntityTypeComponent::type = type;
}
