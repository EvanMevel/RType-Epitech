//
// Created by evans on 31/01/2023.
//

#include "PlayerShootConsumer.h"
#include "Engine/EntityUtils.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"

PlayerShootConsumer::PlayerShootConsumer(Engine &e, const RTypeServerPtr &server) : e(e), server(server) {}

void PlayerShootConsumer::consume(PlayerShootPacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) {
    auto player = e.getScene()->getEntityById(data->playerId);
    auto pos = player->getComponent<PositionComponent>();

    auto projectile = e.getScene()->createEntity();
    entity::initProjectile(projectile, pos->x + 20, pos->y + 20);

    EntityInfoPacket newEntityPacket(projectile);
    server->broadcast(newEntityPacket);
}
