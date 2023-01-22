//
// Created by evans on 21/01/2023.
//

#include "NetworkRemoteServer.h"

NetworkRemoteServer::NetworkRemoteServer(const std::string &address, unsigned short port) : _address(address), _port(port) {
    if (!socket.create()) {
        throw std::runtime_error("Cannot create socket");
    }
}

void NetworkRemoteServer::send(const char *message, int length) {
    socket.sendTo(message, length, _address, _port);
}

bool NetworkRemoteServer::messageReceived(std::string address, int port, char *message, int length) {
    return consumeMessage(message, length);
}

CrossPlatformSocket &NetworkRemoteServer::getSocket() {
    return socket;
}
