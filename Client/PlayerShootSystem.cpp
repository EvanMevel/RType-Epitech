//
// Created by evans on 31/01/2023.
//

#include "PlayerShootSystem.h"
#include "Engine/Network/Packets/PlayerShootPacket.h"

PlayerShootSystem::PlayerShootSystem(const std::shared_ptr<Player> &player) : player(player){

}

void PlayerShootSystem::update(EnginePtr engine) {
    if (cooldown > 0) {
        cooldown--;
    }
    if (player->shoot && cooldown == 0) {
        engine->getModule<ClientNetServer>()->sendPacket(PlayerShootPacket(player->entity->getId()));
        cooldown = 10;
    }
}
