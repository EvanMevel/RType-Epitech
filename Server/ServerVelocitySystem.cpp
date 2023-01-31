//
// Created by evans on 28/01/2023.
//

#include "ServerVelocitySystem.h"
#include "Engine/Engine.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/AccelerationPhysicComponent.h"

void ServerVelocitySystem::entityMoved(Engine &engine, std::shared_ptr<Entity> entity) {

    auto pos = entity->getComponent<PositionComponent>();
    auto physics = entity->getComponent<AccelerationPhysicComponent>();

    EntityVelocityPacket packet(entity->getId(), pos->clone(), physics->velocity.clone(), physics->acceleration.clone(),
                                engine.getCurrentTick());
    srv->broadcast(packet);
}

std::string ServerVelocitySystem::getName() {
    return "ServerVelocitySystem";
}
