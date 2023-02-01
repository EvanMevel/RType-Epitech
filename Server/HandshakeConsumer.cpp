//
// Created by evans on 24/01/2023.
//

#include "HandshakeConsumer.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/HitboxComponent.h"
#include "Engine/Component/TeamComponent.h"
#include "Engine/Network/Packets/PlayerInfoPacket.h"
#include "Engine/TickUtil.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"
#include "Engine/Component/EntityTypeComponent.h"

HandshakeConsumer::HandshakeConsumer(RTypeServerPtr server, Engine &e) : server(server), e(e) {}

static void sendEntitiesInfo(const std::shared_ptr<NetClient>& client, std::shared_ptr<Scene> scene) {
    for (auto &entity : scene->getEntities()) {
        auto comp = entity->getComponent<PositionComponent>();
        auto type = entity->getComponent<EntityTypeComponent>();
        if (comp && type) {
            EntityInfoPacket packet(entity->getId(), type->getType(), comp->getX(), comp->getY());
            client->sendPacket(packet);

            std::cout << "Sent entity info packet " << entity->getId() << std::endl;
        }
    }
}

void HandshakeConsumer::consume(HandshakePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) {
    std::cout << "Handshake received" << std::endl;
    data->handshake = true;

    auto ticker = e.getEngineComponent<TickUtil>();

    unsigned long long startedMs = std::chrono::time_point_cast<std::chrono::milliseconds>(ticker->getStarted()).time_since_epoch().count();

    HandshakeResponsePacket responsePacket(HandshakeResponsePacketType::OK, ticker->getCurrentTick(), startedMs);
    client->sendPacket(responsePacket);

    auto player = e.getScene()->createPlayer();

    data->playerId = player->getId();

    auto comp = player->addComponent<PositionComponent>();
    comp->setX(100);
    comp->setY(100);

    auto tim = player->addComponent<TeamComponent>();
    tim->setTeam(0);

    player->addComponent<HitboxComponent>();

    auto hitbox = player->getComponent<HitboxComponent>();
    hitbox->setLengthX(55);
    hitbox->setLengthY(55);

    PlayerInfoPacket playerInfo;
    playerInfo.playerId = player->getId();
    playerInfo.x = comp->getX();
    playerInfo.y = comp->getY();
    client->sendPacket(playerInfo);

    std::cout << "Sent player info packet" << std::endl;

    sendEntitiesInfo(client, e.getScene());

    std::cout << "Sent entity info packet" << std::endl;

    EntityInfoPacket newPlayerInfo(player->getId(), EntityType::PLAYER, comp->getX(), comp->getY());

    server->broadcast(newPlayerInfo, client);
}
