//
// Created by evans on 24/01/2023.
//

#include <iostream>
#include "HandshakeResponseConsumer.h"
#include "Engine/TickUtil.h"

void HandshakeResponseConsumer::consume(HandshakeResponsePacket &packet, Engine &e) {
    if (packet.getType() != HandshakeResponsePacketType::OK) {
        std::function<void(std::shared_ptr<IGraphicLib>)> func = [](std::shared_ptr<IGraphicLib> lib) {
            if (lib->getWindow().shouldClose()) {
                return;
            }
            lib->closeWindow();
        };

        e.getEngineComponent<IGraphicLib>()->execOnLibThread(func, e.getEngineComponent<IGraphicLib>());
    } else {
        auto ticker = e.getEngineComponent<TickUtil>();

        ticker->setCurrentTick(packet.getCurrentTick());
        ticker->setStarted(packet.getStartedTime());
    }
}

HandshakeResponseConsumer::HandshakeResponseConsumer(RTypeServer server) : ClientPacketConsumer(server) {}
