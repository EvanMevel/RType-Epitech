//
// Created by evans on 31/01/2023.
//

#include "PlayerShootConsumer.h"
#include "Engine/EntityUtils.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"

PlayerShootConsumer::PlayerShootConsumer(EnginePtr e) : RTypePlayerPacketConsumer(e) {}

void PlayerShootConsumer::consume(PlayerShootPacket &packet, std::shared_ptr<NetClient> client,
                                  std::shared_ptr<ClientData> data, std::shared_ptr<Entity> player) {
    auto pos = player->getComponent<PositionComponent>();

    auto projectile = e->getScene()->createEntity();
    entity::initProjectile(projectile, pos->x + 20, pos->y + 20, 10);

    auto team = projectile->addComponent<TeamComponent>();
    team->setTeam(0);

    EntityInfoPacket newEntityPacket(projectile);
    e->getModule<RTypeServer>()->broadcast(newEntityPacket);
}
