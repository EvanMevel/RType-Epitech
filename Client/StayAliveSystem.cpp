//
// Created by evans on 24/01/2023.
//

#include "StayAliveSystem.h"
#include "Engine/TimeUtil.h"
#include "Engine/Network/Packets/PingPacket.h"

void StayAliveSystem::update(EnginePtr engine) {
    auto server = engine->getModule<ClientNetServer>();
    if (server == nullptr || !server->isRunning()) {
        return;
    }
    long long currentTime = getCurrentTime();
    if (currentTime - lastPing > 1000) {
        lastPing = currentTime;
        server->sendPacket(PingPacket::current());
    }
}

std::string StayAliveSystem::getName() {
    return "StayAliveSystem";
}
