//
// Created by evans on 24/01/2023.
//

#include <iostream>
#include "PingPacketConsumer.h"

void PingPacketConsumer::consume(PingPacket &packet, Engine &e) {
    std::cout << "Pong!" << std::endl;
}

PingPacketConsumer::PingPacketConsumer(NetworkRemoteServer<Engine &> &server) : server(server) {}