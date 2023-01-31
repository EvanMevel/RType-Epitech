//
// Created by evans on 24/01/2023.
//

#include "HandshakeConsumer.h"
#include "Engine/Network/Packets/HandshakeResponsePacket.h"
#include "Engine/EntityUtils.h"
#include "Engine/Network/Packets/PlayerInfoPacket.h"
#include "Engine/TickUtil.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"

static void sendEntitiesInfo(const std::shared_ptr<NetClient>& client, std::shared_ptr<Scene> scene) {
    for (auto &entity : scene->getEntities()) {
        auto pos = entity->getComponent<PositionComponent>();
        auto type = entity->getComponent<EntityTypeComponent>();
        if (pos && type) {
            EntityInfoPacket packet(entity, type, pos);
            client->sendPacket(packet);
        }
    }
}

void HandshakeConsumer::consume(HandshakePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) {
    std::cout << "Handshake received" << std::endl;
    data->handshake = true;

    // Send handshake response with tick information
    auto ticker = e.getModule<TickUtil>();
    unsigned long long startedMs = std::chrono::time_point_cast<std::chrono::milliseconds>(ticker->getStarted()).time_since_epoch().count();
    HandshakeResponsePacket responsePacket(HandshakeResponsePacketType::OK, ticker->getCurrentTick(), startedMs);
    client->sendPacket(responsePacket);

    // Init player
    auto player = e.getScene()->createEntity();
    entity::initPlayer(player, 100, 100);
    data->playerId = player->getId();

    // Send player info to client then send all entities to client
    PlayerInfoPacket playerInfo(player);
    client->sendPacket(playerInfo);
    sendEntitiesInfo(client, e.getScene());

    // Send new player info to all other clients
    EntityInfoPacket newPlayerInfo(player);
    e.getModule<RTypeServer>()->broadcast(newPlayerInfo, client);
}

HandshakeConsumer::HandshakeConsumer(Engine &e) : RTypePacketConsumer(e) {}
