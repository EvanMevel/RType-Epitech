// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef R_TYPE_SERVER_NETSERVER_H
#define R_TYPE_SERVER_NETSERVER_H

#include <thread>
#include <utility>
#include <ostream>
#include <functional>
#include <mutex>
#include "CrossPlatformSocket.h"
#include "PacketReceiver.h"
#include "PacketSender.h"
#include "NetworkListener.h"
#include "Engine/Network/Packets/PacketConsumerException.h"
#include "Engine/TimeUtil.h"

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

    std::string addressPort() const;

    friend std::ostream &operator<<(std::ostream &os, const NetClient &client);
};

/**
 * @brief PacketConsumer describes a consumer of packets used by the client
 */
template<class Packet, class Data>
class PacketClientConsumer : public PacketConsumer<Packet, std::shared_ptr<NetClient>, Data> {

};

/**
 * @brief NetServer describes a server that can receive data from clients
 * @tparam Data The type of data that will be passed to the packet consumers
 */
template<class Data>
class NetServer : public NetworkListener, public PacketSender<std::shared_ptr<NetClient>, Data> {
protected:
    const std::string &_address;
    unsigned short _port;
    std::shared_ptr<CrossPlatformSocket> socket;
    std::unordered_map<std::string, std::pair<std::shared_ptr<NetClient>, Data>> clients;
    std::mutex clientsMutex;
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

    size_t getClientCount() const {
        return clients.size();
    }

    void filterClients(std::function<bool (std::shared_ptr<NetClient> &client, Data &data)> filter) {
        std::lock_guard<std::mutex> lock(clientsMutex);
        auto it = clients.begin();
        while (it != clients.end()) {
            if (filter(it->second.first, it->second.second)) {
                it = clients.erase(it);
            } else {
                ++it;
            }
        }
    }

    void forEachClient(std::function<void(std::shared_ptr<NetClient> &client, Data &data)> initPlayer) {
        std::lock_guard<std::mutex> lock(clientsMutex);
        auto it = clients.begin();
        while (it != clients.end()) {
            initPlayer(it->second.first, it->second.second);
            it++;
        }
    }

    virtual void removeClient(std::shared_ptr<NetClient> &client) {
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.erase(client->getAddress() + ":" + std::to_string(client->getPort()));
    }

    virtual Data createData(std::shared_ptr<NetClient> &client) = 0;

    virtual bool clientConnected(std::shared_ptr<NetClient> &client, Data data) = 0;

    virtual void clientDisconnected(std::shared_ptr<NetClient> &client, Data data) = 0;

    void clientMessage(std::shared_ptr<NetClient> &client, Data data, char *message, int length) {
        try {
            this->consumeMessage(message, length, client, data);
        } catch (PacketConsumerException &e) {
            log() << "Client " << client->addressPort() << " kicked. Cause: " << e.what() << std::endl;
            clientDisconnected(client, data);
            removeClient(client);
        }
    }

    void errorReceived(std::string address, int port, int err) override {
        if (address.empty()) {
            address = this->_address;
        }
        std::string key = address + ":" + std::to_string(port);
        auto it = clients.find(key);
        if (it != clients.end()) {
            log() << "Client " << key << " disconnected" << std::endl;
            clientDisconnected(it->second.first, it->second.second);
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients.erase(it);
        }
    }

    template<class Packet>
    void broadcast(const Packet &packet) {
        std::lock_guard<std::mutex> lock(clientsMutex);
        for (auto &client : clients) {
            client.second.first->sendPacket(packet);
        }
    }

    template<class Packet>
    void broadcast(const Packet &packet, std::shared_ptr<NetClient> cli) {
        std::lock_guard<std::mutex> lock(clientsMutex);
        for (auto &client : clients) {
            if (client.second.first != cli) {
                client.second.first->sendPacket(packet);
            }
        }
    }
};

#endif //R_TYPE_SERVER_NETSERVER_H
