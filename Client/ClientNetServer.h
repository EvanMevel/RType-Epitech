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

#ifndef R_TYPE_SERVER_CLIENTNETSERVER_H
#define R_TYPE_SERVER_CLIENTNETSERVER_H

#include "Engine/Engine.h"
#include "Engine/Network/NetworkRemoteServer.h"

/**
 * @brief ClientNetServer is a NetworkRemoteServer that is used by the client to communicate with the server
 */
class ClientNetServer : public NetworkRemoteServer<EnginePtr> {
public:
    ClientNetServer(EnginePtr engine, const std::string &address, unsigned short port) : NetworkRemoteServer(engine, address, port) {}

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
