//
// Created by evans on 22/01/2023.
//

#include <iostream>
#include "NetServer.h"

template<class Data>
NetServer<Data>::NetServer(const std::string &address, unsigned short port)
    : socket(std::make_shared<CrossPlatformSocket>()), _address(address), _port(port) {
    if (!socket->create()) {
        throw std::runtime_error("Cannot create socket");
    }
    if (!socket->bind(address, port)) {
        throw std::runtime_error("Cannot bind socket");
    }
}

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

template<class Data>
bool NetServer<Data>::messageReceived(std::string address, int port, char *message, int length) {
    std::string key = address + ":" + std::to_string(port);
    auto knownClient = clients.find(key);
    if (knownClient == clients.end()) {
        auto cli = std::make_shared<NetClient>(socket, address, port);
        auto clientPair = std::make_pair(cli, createData(cli));
        clients[key] = clientPair;
        clientConnected(clientPair.first, clientPair.second);
        clientMessage(clientPair.first, clientPair.second, message, length);
    } else {
        clientMessage(knownClient->second.first, knownClient->second.second, message, length);
    }
    return true;
}

template<class Data>
CrossPlatformSocket &NetServer<Data>::getSocket() {
    return *socket;
}

template<class Data>
void NetServer<Data>::clientMessage(std::shared_ptr<NetClient> &client, Data &data, char *message, int length) {
    this->consumeMessage(message, length, client, data);
}

template<class Data>
void NetServer<Data>::errorReceived(std::string address, int port, int err) {
    if (address.empty()) {
        address = this->_address;
    }
    std::string key = address + ":" + std::to_string(port);
    auto it = clients.find(key);
    if (it != clients.end()) {
        std::cout << "Client " << key << " disconnected" << std::endl;
        clients.erase(it);
    }
}