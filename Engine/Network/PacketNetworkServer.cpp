//
// Created by evans on 21/01/2023.
//

#include "PacketNetworkServer.h"

bool PacketNetworkClient::messageReceived(std::string address, int port, char *message, int length) {
    return consumeMessage(message, length);
}

PacketNetworkClient::PacketNetworkClient(const CrossPlatformSocket &socket, const std::string &address,
                                         unsigned short port) : NetworkClient(socket, address, port) {}

PacketNetworkClient::~PacketNetworkClient() {

}

void PacketNetworkClient::send(const char *message, int length) {
    NetworkClient::send(message, length);
}

PacketNetworkServer::PacketNetworkServer(const std::string &address, unsigned short port) : NetworkServer(address,
                                                                                                          port) {}
