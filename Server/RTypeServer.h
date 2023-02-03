//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_RTYPESERVER_H
#define R_TYPE_SERVER_RTYPESERVER_H

#define MAX_CLIENTS 4


#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Network/NetServer.h"
#include "ClientData.h"

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

template<class Packet>
class RTypePacketConsumer : public PacketClientConsumer<Packet, std::shared_ptr<ClientData>> {
protected:
    EnginePtr e;
public:
    explicit RTypePacketConsumer(EnginePtr e) : e(e) {}
};

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
