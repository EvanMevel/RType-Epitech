//
// Created by evans on 27/01/2023.
//

#include <iostream>
#include <utility>
#include "PlayerInfoConsumer.h"
#include "Engine/EntityUtils.h"
#include "Client/FixTextureComponent.h"
#include "Client/Player.h"
#include "Client/PlayerKeysSystem.h"
#include "Client/PlayerMoveSystem.h"
#include "Client/PlayerShootSystem.h"

void PlayerInfoConsumer::consume(PlayerInfoPacket &packet, Engine &e) {
    auto player = e.getScene()->getEntityById(packet.playerId);
    entity::initPlayer(player, packet.x, packet.y);

    auto texture = player->getOrCreate<FixTextureComponent>();
    texture->setTexture(playerTexture);

    std::cout << ">> We are player " << packet.playerId << std::endl;

    std::shared_ptr<Player> pl = std::make_shared<Player>();
    pl->entity = player;

    e.getModule<IGraphicLib>()->addSystem<PlayerKeysSystem>(pl);

    e.getScene()->addSystem<PlayerMoveSystem>(pl);
    e.getScene()->addSystem<PlayerShootSystem>(pl);
}

PlayerInfoConsumer::PlayerInfoConsumer(std::shared_ptr<ITexture> playerTexture, const RTypeServer &srv) : playerTexture(std::move(
        playerTexture)), server(srv) {}
