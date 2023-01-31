//
// Created by evans on 31/01/2023.
//

#include "PlayerMoveConsumer.h"
#include "Engine/Component/AccelerationPhysicComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Engine/TickUtil.h"

void PlayerMoveConsumer::consume(PlayerMovePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) {
    auto player = e.getScene()->getEntityById(data->playerId);
    auto physics = player->getOrCreate<AccelerationPhysicComponent>();
    physics->acceleration = packet.acceleration;

    auto ticker = e.getEngineComponent<TickUtil>();

    auto pos = player->getComponent<PositionComponent>();

    EntityVelocityPacket velPacket(player->getId(), pos->clone(), physics->velocity.clone(), physics->acceleration.clone(),
                                ticker->getCurrentTick());
    server->broadcast(velPacket);
}

PlayerMoveConsumer::PlayerMoveConsumer(Engine &e, RTypeServerPtr server) : e(e), server(server) {}
