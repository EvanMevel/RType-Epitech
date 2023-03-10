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

#include <iostream>
#include "NetServer.h"


void NetClient::send(const char *message, int length) {
    bool sent = socket->sendTo(message, length, address, port);
    if (!sent) {
        std::cout << "Cannot send message to " << address << ":" << port << std::endl;
    }
}

NetClient::NetClient(const std::shared_ptr<CrossPlatformSocket> &socket, const std::string &address,
                     unsigned short port) : socket(socket), address(address), port(port) {}

unsigned short NetClient::getPort() const {
    return port;
}

const std::string &NetClient::getAddress() const {
    return address;
}

NetClient::~NetClient() {

}

NetClient::NetClient(const NetClient &other) : socket(other.socket), address(other.address), port(other.port) {

}

std::ostream &operator<<(std::ostream &os, const NetClient &client) {
    os << client.addressPort();
    return os;
}

std::string NetClient::addressPort() const {
    return address + ":" + std::to_string(port);
}
