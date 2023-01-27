//
// Created by evans on 24/01/2023.
//

#include "HandshakeConsumer.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Network/Packets/PlayerInfoPacket.h"

HandshakeConsumer::HandshakeConsumer(RTypeServer &server, Engine &e) : server(server), e(e) {}

void HandshakeConsumer::consume(HandshakePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) {
    std::cout << "Handshake received" << std::endl;
    data->handshake = true;

    HandshakeResponsePacket responsePacket(HandshakeResponsePacketType::OK);
    client->sendPacket(responsePacket);

    Entity &player = e.getScene()->createPlayer();

    data->playerId = player.getId();

    auto comp = player.addComponent<PositionComponent>();
    comp->setX(100);
    comp->setY(100);

    PlayerInfoPacket playerInfo;
    playerInfo.playerId = (int) player.getId();
    playerInfo.x = comp->getX();
    playerInfo.y = comp->getY();
    client->sendPacket(playerInfo);
}
