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

        e.getModule<IGraphicLib>()->execOnLibThread(func, e.getModule<IGraphicLib>());
    } else {
        auto ticker = e.getModule<TickUtil>();

        ticker->setCurrentTick(packet.getCurrentTick());
        ticker->setStarted(packet.getStartedTime());
    }
}