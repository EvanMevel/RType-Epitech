//
// Created by evans on 24/01/2023.
//

#include "HandshakeConsumer.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Network/Packets/PlayerInfoPacket.h"
#include "Engine/TickUtil.h"

HandshakeConsumer::HandshakeConsumer(RTypeServerPtr server, Engine &e) : server(server), e(e) {}

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

    PlayerInfoPacket playerInfo;
    playerInfo.playerId = (int) player->getId();
    playerInfo.x = comp->getX();
    playerInfo.y = comp->getY();
    client->sendPacket(playerInfo);

    std::cout << "Sent player info packet" << std::endl;
}
