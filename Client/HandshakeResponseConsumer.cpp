//
// Created by evans on 24/01/2023.
//

#include <iostream>
#include "HandshakeResponseConsumer.h"

HandshakeResponseConsumer::HandshakeResponseConsumer(NetworkRemoteServer<Engine &> &server) : server(server) {

}

void HandshakeResponseConsumer::consume(HandshakeResponsePacket &packet, Engine &e) {
    std::cout << "Handshake response received" << packet.getType() << std::endl;
}
