//
// Created by evans on 27/01/2023.
//

#include <iostream>
#include <utility>
#include "PlayerInfoConsumer.h"
#include "Engine/Component/PositionComponent.h"
#include "Client/FixTextureComponent.h"
#include "Client/Player.h"
#include "Client/PlayerKeysSystem.h"
#include "Client/PlayerMoveSystem.h"
#include "Engine/Component/AccelerationPhysicComponent.h"

void PlayerInfoConsumer::consume(PlayerInfoPacket &packet, Engine &e) {

    auto sc = e.getScene();
    auto player = sc->getEntityById(packet.playerId);
    auto pos = player->getOrCreate<PositionComponent>();
    auto physic = player->addComponent<AccelerationPhysicComponent>();
    physic->maxVelocity = 15;

    pos->setX(packet.x);
    pos->setY(packet.y);

    auto texture = player->getOrCreate<FixTextureComponent>();
    texture->setTexture(playerTexture);

    std::cout << "|||| We are player " << packet.playerId << " at " << packet.x << " " << packet.y << std::endl;

    std::shared_ptr<Player> pl = std::make_shared<Player>();
    pl->entity = player;

    e.getGraphicLib()->addSystem<PlayerKeysSystem>(pl);

    e.getScene()->addSystem<PlayerMoveSystem>(pl, server);
}

PlayerInfoConsumer::PlayerInfoConsumer(ITexture playerTexture, const RTypeServer &srv) : playerTexture(std::move(
        playerTexture)), server(srv) {}
