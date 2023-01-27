//
// Created by evans on 24/01/2023.
//

#include <iostream>
#include "HandshakeResponseConsumer.h"

HandshakeResponseConsumer::HandshakeResponseConsumer(NetworkRemoteServer<Engine &> &server) : server(server) {

}

void HandshakeResponseConsumer::consume(HandshakeResponsePacket &packet, Engine &e) {
    if (packet.getType() != HandshakeResponsePacketType::OK) {
        e.getGraphicLib()->execOnLibThread([] (std::shared_ptr<IGraphicLib> lib) {
            if (lib->getWindow().shouldClose()) {
                return;
            }
            lib->closeWindow();
        });
    }
}
