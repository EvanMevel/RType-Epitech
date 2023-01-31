//
// Created by evans on 31/01/2023.
//

#include "PlayerMoveConsumer.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Engine/TickUtil.h"

PlayerMoveConsumer::PlayerMoveConsumer(Engine &e) : RTypePlayerPacketConsumer(e) {}

void PlayerMoveConsumer::consume(PlayerMovePacket &packet, std::shared_ptr<NetClient> client,
                                 std::shared_ptr<ClientData> data, std::shared_ptr<Entity> player) {
    auto physics = player->getOrCreate<AccelerationPhysicComponent>();
    physics->acceleration = packet.acceleration;

    auto ticker = e.getModule<TickUtil>();

    EntityVelocityPacket velPacket(player, ticker->getCurrentTick());
    e.getModule<RTypeServer>()->broadcast(velPacket);
}
