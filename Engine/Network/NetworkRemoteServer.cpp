//
// Created by evans on 21/01/2023.
//

#include <iostream>
#include "NetworkRemoteServer.h"

template<class Data>
NetworkRemoteServer<Data>::NetworkRemoteServer(Data dat, const std::string &address, unsigned short port) : data(dat), _address(address), _port(port) {
    if (!socket.create()) {
        throw std::runtime_error("Cannot create socket");
    }
}

template<class Data>
void NetworkRemoteServer<Data>::send(const char *message, int length) {
    socket.sendTo(message, length, _address, _port);
}

template<class Data>
bool NetworkRemoteServer<Data>::messageReceived(std::string address, int port, char *message, int length) {
    return this->consumeMessage(message, length, data);
}

template<class Data>
CrossPlatformSocket &NetworkRemoteServer<Data>::getSocket() {
    return socket;
}

template<class Data>
void NetworkRemoteServer<Data>::errorReceived(std::string address, int port, int err) {
    std::cout << "Error received: " << err << std::endl;
}
