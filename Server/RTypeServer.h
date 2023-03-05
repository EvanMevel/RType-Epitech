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

#ifndef R_TYPE_SERVER_RTYPESERVER_H
#define R_TYPE_SERVER_RTYPESERVER_H

#define MAX_CLIENTS 4


#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Network/NetServer.h"
#include "ClientData.h"

/**
 * @brief Server class that handles the connection of clients
 */
class RTypeServer : public NetServer<std::shared_ptr<ClientData>>, public SystemHolder {
private:
    EnginePtr engine;
public:
    RTypeServer(EnginePtr engine, const std::string &address, unsigned short port);

    ~RTypeServer() override;

    std::shared_ptr<ClientData> createData(std::shared_ptr<NetClient> &client) override;

    bool clientConnected(std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> data) override;

    void clientDisconnected(std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> data) override;
};

/**
 * @brief Packet consumer that handles the packets received by the server
 */
template<class Packet>
class RTypePacketConsumer : public PacketClientConsumer<Packet, std::shared_ptr<ClientData>> {
protected:
    EnginePtr e;
public:
    explicit RTypePacketConsumer(EnginePtr e) : e(e) {}
};

/**
 * @brief Packet consumer that handles the packets received by the server that are related to a player
 */
template<class Packet>
class RTypePlayerPacketConsumer : public RTypePacketConsumer<Packet> {
public:
    explicit RTypePlayerPacketConsumer(EnginePtr e) : RTypePacketConsumer<Packet>(e) {}

    void consume(Packet &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) override {
        data->hasShakeHands();
        auto player = this->e->getScene()->getEntityById(data->playerId);
        this->consume(packet, client, data, player);
    }

    virtual void consume(Packet &packet, std::shared_ptr<NetClient> client,
                         std::shared_ptr<ClientData> data, std::shared_ptr<Entity> player) = 0;
};

using RTypeServerPtr = std::shared_ptr<RTypeServer>;


#endif //R_TYPE_SERVER_RTYPESERVER_H
