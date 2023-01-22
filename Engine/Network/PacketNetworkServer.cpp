//
// Created by evans on 21/01/2023.
//

#include "PacketNetworkServer.h"

PacketConsumers &PacketNetworkClient::getConsumers() {
    return packetConsumers;
}

bool PacketNetworkClient::messageReceived(std::string address, int port, char *message, int length) {
    unsigned char magic = *message;
    if (magic != this->_magic) {
        return false;
    }
    ByteArray arr;
    arr.write(message + 1, length - 1);
    packetConsumers.consume(arr);
    return false;
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
