//
// Created by evans on 20/01/2023.
//

#include <iostream>
#include "NetworkListener.h"

void NetworkListener::startListening() {
    listeningThread = std::make_unique<std::thread>(&NetworkListener::listen, this);
    running.store(true);
}

void NetworkListener::listen() {
    while (running.load()) {
        char buffer[4096];
        std::string address;
        unsigned short port;
        int recv_len = getSocket().recvFrom(buffer, 4096, address, port);
        if (getSocket().isClosed() || !running.load()) {
            return;
        }
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
    if (running.load() && listeningThread != nullptr && listeningThread->joinable()) {
        running.store(false);
        listeningThread->join();
    }
}

bool NetworkListener::isRunning() const {
    return running.load();
}
