//
// Created by evans on 20/01/2023.
//

#include <iostream>
#include "NetworkClient.h"

NetworkClient::NetworkClient(const CrossPlatformSocket &socket, const std::string &address, unsigned short port)
        : socket(socket), address(address), port(port) {}

void NetworkClient::send(const char *message, int length) {
    socket.sendTo(message, length, address, port);
}

CrossPlatformSocket &NetworkClient::getSocket() {
    return socket;
}