//
// Created by evans on 28/01/2023.
//

#include "ServerVelocitySystem.h"
#include "Engine/Engine.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/VelocityComponent.h"
#include "Engine/Component/AccelerationComponent.h"

void ServerVelocitySystem::entityMoved(std::shared_ptr<Entity> entity) {

    auto pos = entity->getComponent<PositionComponent>();
    auto vel = entity->getComponent<VelocityComponent>();
    auto accel = entity->getComponent<AccelerationComponent>();

    EntityVelocityPacket packet((int) entity->getId(), pos->clone(), vel->clone(), accel->clone());
    srv->broadcast(packet);
}

std::string ServerVelocitySystem::getName() {
    return "ServerVelocitySystem";
}
