//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_CLIENTNETSERVER_H
#define R_TYPE_SERVER_CLIENTNETSERVER_H

#include "Engine/Network/NetworkRemoteServer.h"
#include "Engine/Engine.h"

class ClientNetServer : public NetworkRemoteServer<Engine&> {
public:
    ClientNetServer(Engine &dat, const std::string &address, unsigned short port) : NetworkRemoteServer(dat, address, port) {}

    ClientNetServer(const ClientNetServer &other) : NetworkRemoteServer(other) {}

    ~ClientNetServer() override {

    }
};

using RTypeServer = std::shared_ptr<NetworkRemoteServer<Engine&>>;

template<class Packet>
class ClientPacketConsumer : public PacketConsumer<Packet, Engine&> {
private:
    RTypeServer server;
public:
    explicit ClientPacketConsumer(RTypeServer server) : server(server) {}
};

#endif //R_TYPE_SERVER_CLIENTNETSERVER_H
