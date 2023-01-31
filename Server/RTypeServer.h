//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_RTYPESERVER_H
#define R_TYPE_SERVER_RTYPESERVER_H

#define MAX_CLIENTS 4


#include <iostream>
#include "Engine/Network/NetServer.h"
#include "Engine/Network/Packets/PingPacket.h"
#include "ClientData.h"
#include "Engine/SystemHolder.h"
#include "Engine/Network/Packets/HandshakeResponsePacket.h"

class RTypeServer : public NetServer<std::shared_ptr<ClientData>>, public SystemHolder {
public:
    RTypeServer(const std::string &address, unsigned short port) : NetServer(address, port) {}

    ~RTypeServer() override {

    }

    std::shared_ptr<ClientData> createData(std::shared_ptr<NetClient> &client) override {
        return std::make_shared<ClientData>();
    }

    bool clientConnected(std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> data) override {
        if (clients.size() >= MAX_CLIENTS) {
            std::cout << client->addressPort() << " kicked. Cause: too many clients already connected" << std::endl;
            client->sendPacket(HandshakeResponsePacket(HandshakeResponsePacketType::FULL, 0, 0));
            return false;
        }
        std::cout << "Client " << client->addressPort() << " connected" << std::endl;
        return true;
    }

};

using RTypeServerPtr = std::shared_ptr<RTypeServer>;


#endif //R_TYPE_SERVER_RTYPESERVER_H
