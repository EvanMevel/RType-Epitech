//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_CLIENTNETSERVER_H
#define R_TYPE_SERVER_CLIENTNETSERVER_H

#include "Engine/Engine.h"
#include "Engine/Network/NetworkRemoteServer.h"

class ClientNetServer : public NetworkRemoteServer<EnginePtr> {
public:
    ClientNetServer(EnginePtr engine, const std::string &address, unsigned short port) : NetworkRemoteServer(engine, address, port) {}

    ClientNetServer(const ClientNetServer &other) : NetworkRemoteServer(other) {}

    ~ClientNetServer() override {

    }

    void errorReceived(std::string address, int port, int err) override {
        std::function<void(std::shared_ptr<IGraphicLib>)> func = [](std::shared_ptr<IGraphicLib> lib) {
            if (lib->getWindow().shouldClose()) {
                return;
            }
            lib->closeWindow();
        };

        this->data->getModule<IGraphicLib>()->execOnLibThread(func, this->data->getModule<IGraphicLib>());
    }
};

using RTypeServer = std::shared_ptr<ClientNetServer>;

template<class Packet>
class ClientPacketConsumer : public PacketConsumer<Packet, EnginePtr> {
public:
    virtual void consume(Packet &packet, EnginePtr engine, RTypeServer server) = 0;

    void consume(Packet &packet, EnginePtr engine) override {
        RTypeServer server = engine->getModule<ClientNetServer>();
        if (server) {
            consume(packet, engine, server);
        }
    }
};

#endif //R_TYPE_SERVER_CLIENTNETSERVER_H
