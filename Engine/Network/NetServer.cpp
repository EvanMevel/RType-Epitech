//
// Created by evans on 22/01/2023.
//

#include <iostream>
#include "NetServer.h"


void NetClient::send(const char *message, int length) {
    bool sent = socket->sendTo(message, length, address, port);
    if (!sent) {
        std::cout << "Cannot send message to " << address << ":" << port << std::endl;
    }
}

NetClient::NetClient(const std::shared_ptr<CrossPlatformSocket> &socket, const std::string &address,
                     unsigned short port) : socket(socket), address(address), port(port) {}

unsigned short NetClient::getPort() const {
    return port;
}

const std::string &NetClient::getAddress() const {
    return address;
}

NetClient::~NetClient() {

}

NetClient::NetClient(const NetClient &other) : socket(other.socket), address(other.address), port(other.port) {

}

std::ostream &operator<<(std::ostream &os, const NetClient &client) {
    os << client.addressPort();
    return os;
}

std::string NetClient::addressPort() const {
    return address + ":" + std::to_string(port);
}
