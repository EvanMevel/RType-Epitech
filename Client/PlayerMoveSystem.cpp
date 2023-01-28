//
// Created by evans on 28/01/2023.
//

#include "PlayerMoveSystem.h"
#include "Engine/Component/AccelerationComponent.h"
#include "Engine/Network/Packets/PlayerMovePacket.h"

PlayerMoveSystem::PlayerMoveSystem(const std::shared_ptr<Player> &player, const RTypeServer &server) : player(player),
                                                                                                       server(server) {}

void PlayerMoveSystem::update(Engine &engine) {
    Vector2i acceleration = {0, 0};
    if (player->up) {
        acceleration.y -= 3;
    }
    if (player->down) {
        acceleration.y += 3;
    }
    if (player->left) {
        acceleration.x -= 3;
    }
    if (player->right) {
        acceleration.x += 3;
    }
    if (acceleration.length() == 0) {
        return;
    }
    auto accel = player->entity->getOrCreate<AccelerationComponent>();
    accel->setX(acceleration.x);
    accel->setY(acceleration.y);

    server->sendPacket(PlayerMovePacket((int) player->entity->getId(), acceleration));
}
