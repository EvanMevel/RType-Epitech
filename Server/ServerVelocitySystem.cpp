//
// Created by evans on 28/01/2023.
//

#include "ServerVelocitySystem.h"
#include "Engine/Engine.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"

void ServerVelocitySystem::entityMoved(Engine &engine, std::shared_ptr<Entity> entity) {
    EntityVelocityPacket packet(entity, engine.getCurrentTick());
    srv->broadcast(packet);
}

std::string ServerVelocitySystem::getName() {
    return "ServerVelocitySystem";
}
