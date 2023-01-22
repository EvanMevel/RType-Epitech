//
// Created by evans on 20/01/2023.
//

#include <iostream>
#include "NetworkListener.h"

void NetworkListener::startListening() {
    listeningThread = std::thread(&NetworkListener::listen, this);
}

void NetworkListener::listen() {
    while (true) {
        char buffer[4096];
        std::string address;
        unsigned short port;
        int recv_len = getSocket().recvFrom(buffer, 4096, address, port);
        if (recv_len > 0) {
            std::cout << "Received message from " << address << ":" << port << ": " << buffer << std::endl;
            messageReceived(address, port, buffer, recv_len);
        } else {
            std::cout << "Failed to receive message" << std::endl;
            return;
        }
    }
}

NetworkListener::~NetworkListener() {
    if (listeningThread.joinable()) {
        listeningThread.join();
    }
}
