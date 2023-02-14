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
#include "NetworkListener.h"

void NetworkListener::startListening() {
    listeningThread = std::make_unique<std::thread>(&NetworkListener::listen, this);
    running.store(true);
}

void NetworkListener::listen() {
    fd_set rfds;

    char buffer[4096];
    std::string address;
    unsigned short port;

    int recVal;

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 25;

    while (running.load()) {

        FD_ZERO(&rfds);
        FD_SET(getSocket().getSocket(), &rfds);

        recVal = select(getSocket().getSocket() + 1, &rfds, nullptr, nullptr, &tv);

        if (getSocket().isClosed() || !running.load()) {
            return;
        }
        if (recVal == -1) {
            std::cout << "Error in select()" << std::endl;
            return;
        }
        if (recVal == 0) {
            continue;
        }
        int recv_len = getSocket().recvFrom(buffer, 4096, address, port);
        if (recv_len > 0) {
            //std::cout << "Received message from " << address << ":" << port << ": " << buffer << std::endl;
            messageReceived(address, port, buffer, recv_len);
        } else {
            if (address.empty()) {
                errorReceived(getSocket().lastAddress, getSocket().lastPort, recv_len);
            } else {
                errorReceived(address, port, recv_len);
            }
        }
    }
}

NetworkListener::~NetworkListener() {
    running.store(false);
    if (listeningThread != nullptr && listeningThread->joinable()) {
        listeningThread->join();
    }
}

bool NetworkListener::isRunning() const {
    return running.load();
}
