//
// Created by evans on 28/01/2023.
//

#include "PlayerMoveSystem.h"
#include "Engine/Network/Packets/PlayerMovePacket.h"
#include "Engine/Component/AccelerationPhysicComponent.h"

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
    if (acceleration.lengthSquare() == 0) {
        return;
    }
    auto physic = player->entity->getOrCreate<AccelerationPhysicComponent>();
    physic->acceleration = acceleration;

    server->sendPacket(PlayerMovePacket((int) player->entity->getId(), acceleration));
}
