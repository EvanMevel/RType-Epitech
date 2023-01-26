//
// Created by evans on 24/01/2023.
//

#include "HandshakeConsumer.h"

HandshakeConsumer::HandshakeConsumer(RTypeServer &server) : server(server) {}

void HandshakeConsumer::consume(HandshakePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) {
    std::cout << "Handshake received" << std::endl;
    data->handshake = true;

    HandshakeResponsePacket responsePacket(HandshakeResponsePacketType::OK);
    client->sendPacket(responsePacket);
}
