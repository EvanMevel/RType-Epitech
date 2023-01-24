//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_RTYPESERVER_H
#define R_TYPE_SERVER_RTYPESERVER_H


#include <iostream>
#include "Engine/Network/NetServer.h"
#include "Engine/Network/Packets/PingPacket.h"
#include "ClientData.h"
#include "Engine/SystemHolder.h"

class RTypeServer : public NetServer<ClientData>, public SystemHolder {
public:
    RTypeServer(const std::string &address, unsigned short port) : NetServer(address, port) {}

    ClientData createData(std::shared_ptr<NetClient> &client) override {
        return ClientData();
    }

    void clientConnected(std::shared_ptr<NetClient> &client, ClientData &data) override {
        std::cout << "Client connected " << client->getAddress() << ":" << client->getPort() << std::endl;
    }
};


#endif //R_TYPE_SERVER_RTYPESERVER_H
