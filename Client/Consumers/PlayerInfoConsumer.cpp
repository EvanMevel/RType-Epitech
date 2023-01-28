//
// Created by evans on 27/01/2023.
//

#include <iostream>
#include <utility>
#include "PlayerInfoConsumer.h"
#include "Engine/Component/PositionComponent.h"
#include "Client/FixTextureComponent.h"

void PlayerInfoConsumer::consume(PlayerInfoPacket &packet, Engine &e) {

    auto sc = e.getScene();
    auto player = sc->getEntityById(packet.playerId);
    auto pos = player->getOrCreate<PositionComponent>();

    pos->setX(packet.x);
    pos->setY(packet.y);

    auto texture = player->getOrCreate<FixTextureComponent>();
    texture->setTexture(playerTexture);

    std::cout << "|||| We are player " << packet.playerId << " at " << packet.x << " " << packet.y << std::endl;
}

PlayerInfoConsumer::PlayerInfoConsumer(ITexture playerTexture) : playerTexture(std::move(playerTexture)) {}
