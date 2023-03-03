//
// Created by aaama on 27/02/2023.
//

#include "EntityLinkComponent.h"

EntityLinkComponent::EntityLinkComponent() {}

EntityLinkComponent::~EntityLinkComponent() {

}

EntityLinkComponent::EntityLinkComponent(const std::shared_ptr<Entity> &entity) : entity(entity) {

}
