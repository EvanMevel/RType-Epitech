//
// Created by evans on 22/01/2023.
//

#ifndef R_TYPE_SERVER_NETSERVER_H
#define R_TYPE_SERVER_NETSERVER_H

#include <thread>
#include <utility>
#include <ostream>
#include "CrossPlatformSocket.h"
#include "PacketReceiver.h"
#include "PacketSender.h"
#include "NetworkListener.h"
#include "Engine/Network/Packets/PacketConsumerException.h"

/**
 * @brief NetClient describes a client connected to the server
 */
class NetClient : public PacketReceiver {
protected:
    std::shared_ptr<CrossPlatformSocket> socket;
    std::string address;
    unsigned short port;
public:
    NetClient(const std::shared_ptr<CrossPlatformSocket> &socket, const std::string &address, unsigned short port);

    NetClient(const NetClient &other);

    ~NetClient() override;

    void send(const char *message, int length) override;

    const std::string &getAddress() const;

    unsigned short getPort() const;

    friend std::ostream &operator<<(std::ostream &os, const NetClient &client);
};

template<class Packet, class Data>
class PacketClientConsumer : public PacketConsumer<Packet, std::shared_ptr<NetClient>, Data> {

};

/**
 * @brief NetServer describes a server that can receive data from clients
 * @tparam Data The type of data that will be passed to the packet consumers
 */
template<class Data>
class NetServer : public NetworkListener , public PacketSender<std::shared_ptr<NetClient>, Data> {
protected:
    const std::string &_address;
    unsigned short _port;
    std::shared_ptr<CrossPlatformSocket> socket;
    std::unordered_map<std::string, std::pair<std::shared_ptr<NetClient>, Data>> clients;
public:
    NetServer(const std::string &address, unsigned short port) : socket(std::make_shared<CrossPlatformSocket>()), _address(address), _port(port) {
        if (!socket->create()) {
            throw std::runtime_error("Cannot create socket");
        }
        if (!socket->bind(address, port)) {
            throw std::runtime_error("Cannot bind socket");
        }
    }

    ~NetServer() override {

    }

    bool messageReceived(std::string address, int port, char *message, int length) override {
        std::string key = address + ":" + std::to_string(port);
        auto knownClient = clients.find(key);
        if (knownClient == clients.end()) {
            auto cli = std::make_shared<NetClient>(socket, address, port);
            auto clientPair = std::make_pair(cli, createData(cli));
            if (clientConnected(clientPair.first, clientPair.second)) {
                clients[key] = clientPair;
                clientMessage(clientPair.first, clientPair.second, message, length);
            } else {
                return false;
            }
        } else {
            clientMessage(knownClient->second.first, knownClient->second.second, message, length);
        }
        return true;
    }

    CrossPlatformSocket &getSocket() override {
        return *socket;
    }

    std::unordered_map<std::string, std::pair<std::shared_ptr<NetClient>, Data>> &getClients() {
        return clients;
    }

    virtual Data createData(std::shared_ptr<NetClient> &client) = 0;

    virtual bool clientConnected(std::shared_ptr<NetClient> &client, Data data) = 0;

    void clientMessage(std::shared_ptr<NetClient> &client, Data data, char *message, int length) {
        try {
            this->consumeMessage(message, length, client, data);
        } catch (PacketConsumerException &e) {
            clients.erase(client->getAddress() + ":" + std::to_string(client->getPort()));
            std::cout << "Client " << client << " kicked. Cause: " << e.what() << std::endl;
        }
    }

    void errorReceived(std::string address, int port, int err) override {
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

    template<class Packet>
    void broadcast(const Packet &packet) {
        for (auto &client : clients) {
            client.second.first->sendPacket(packet);
        }
    }
};

template class NetServer<int>;

#endif //R_TYPE_SERVER_NETSERVER_H
