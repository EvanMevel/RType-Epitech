//
// Created by evans on 20/01/2023.
//

#include <stdexcept>
#include <iostream>
#include "NetworkServer.h"

NetworkServer::NetworkServer(const std::string &address, unsigned short port) {
    if (!socket.create()) {
        throw std::runtime_error("Cannot create socket");
    }
    if (!socket.bind(address, port)) {
        throw std::runtime_error("Cannot bind socket");
    }
}

NetworkServer::~NetworkServer() {
    listeningThread.join();
}

bool NetworkServer::messageReceived(std::string address, int port, char *message, int length) {
    _clients.emplace_back(socket, address, port);
    _clients.back().startListening();
    return clientConnected(_clients.back());
}

CrossPlatformSocket &NetworkServer::getSocket() {
    return socket;
}
