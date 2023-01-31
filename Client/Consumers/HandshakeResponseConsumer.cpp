//
// Created by evans on 24/01/2023.
//

#include <iostream>
#include "HandshakeResponseConsumer.h"

void HandshakeResponseConsumer::consume(HandshakeResponsePacket &packet, Engine &e) {
    if (packet.getType() != HandshakeResponsePacketType::OK) {
        std::function<void(std::shared_ptr<IGraphicLib>)> func = [](std::shared_ptr<IGraphicLib> lib) {
            if (lib->getWindow().shouldClose()) {
                return;
            }
            lib->closeWindow();
        };

        e.getGraphicLib()->execOnLibThread(func, e.getGraphicLib());
    } else {
        e.setCurrentTick(packet.getCurrentTick());
    }
}

HandshakeResponseConsumer::HandshakeResponseConsumer(RTypeServer server) : ClientPacketConsumer(server) {}
