//
// Created by evans on 20/01/2023.
//

#include <stdexcept>
#include "PacketNetworkServer.h"

template<class Client>
NetworkServer<Client>::NetworkServer(const std::string &address, unsigned short port) {
    if (!socket.create()) {
        throw std::runtime_error("Cannot create socket");
    }
    if (!socket.bind(address, port)) {
        throw std::runtime_error("Cannot bind socket");
    }
}


template<class Client>
bool NetworkServer<Client>::messageReceived(std::string address, int port, char *message, int length) {
    _clients.emplace_back(socket, address, port);
    _clients.back().startListening();
    clientConnected(_clients.back());
    return _clients.back().messageReceived(address, port, message, length);
}

template<class Client>
CrossPlatformSocket &NetworkServer<Client>::getSocket() {
    return socket;
}

template<class Client>
NetworkServer<Client>::~NetworkServer() {

}
