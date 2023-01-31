//
// Created by evans on 28/01/2023.
//

#include "ServerVelocitySystem.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Engine/TickUtil.h"
#include "RTypeServer.h"

ServerVelocitySystem::ServerVelocitySystem() {}

void ServerVelocitySystem::entityMoved(Engine &engine, std::shared_ptr<Entity> entity) {
    auto ticker = engine.getModule<TickUtil>();

    EntityVelocityPacket packet(entity, ticker->getCurrentTick());
    engine.getModule<RTypeServer>()->broadcast(packet);
}

std::string ServerVelocitySystem::getName() {
    return "ServerVelocitySystem";
}
