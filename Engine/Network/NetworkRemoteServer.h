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

#ifndef R_TYPE_SERVER_NETWORKREMOTESERVER_H
#define R_TYPE_SERVER_NETWORKREMOTESERVER_H

#include "CrossPlatformSocket.h"
#include "NetworkListener.h"
#include "PacketReceiver.h"
#include "PacketSender.h"
#include "Packets/PacketConsumers.h"
#include "Engine/SystemHolder.h"

/**
 * @brief NetworkRemoteServer is a class that represents a remote server.
 * @details It is used to send and receive packets to and from a remote server.
 * @details It is also used to listen to incoming packets from the remote server.
 */
template<class Data>
class NetworkRemoteServer : public NetworkListener, public PacketReceiver, public PacketSender<Data>, public SystemHolder {
protected:
    Data data;
    std::shared_ptr<CrossPlatformSocket> socket;
    std::string _address;
    unsigned short _port;
public:
    const std::string &getAddress() const {
        return _address;
    }

    void setAddress(const std::string &address) {
        _address = address;
    }

    unsigned short getPort() const {
        return _port;
    }

    void setPort(unsigned short port) {
        _port = port;
    }

    NetworkRemoteServer(Data dat, const std::string &address, unsigned short port) : socket(std::make_shared<CrossPlatformSocket>()),
        data(dat), _address(address), _port(port) {
        if (!socket->create()) {
            throw std::runtime_error("Cannot create socket");
        }
    }

    ~NetworkRemoteServer() override {
    }

    void send(const char *message, int length) override {
        socket->sendTo(message, length, _address, _port);
    }

    bool messageReceived(std::string address, int port, char *message, int length) override {
        return this->consumeMessage(message, length, data);
    }

    void errorReceived(std::string address, int port, int err) override {
        std::cout << "Error received: " << err << std::endl;
    }

    CrossPlatformSocket &getSocket() override {
        return *socket;
    }
};

#endif //R_TYPE_SERVER_NETWORKREMOTESERVER_H
