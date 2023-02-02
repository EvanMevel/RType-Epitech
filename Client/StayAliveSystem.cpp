//
// Created by evans on 24/01/2023.
//

#include "StayAliveSystem.h"
#include "Engine/TimeUtil.h"
#include "Engine/Network/Packets/PingPacket.h"

void StayAliveSystem::update(EnginePtr engine) {
    long long currentTime = getCurrentTime();
    if (currentTime - lastPing > 1000) {
        lastPing = currentTime;
        engine->getModule<ClientNetServer>()->sendPacket(PingPacket::current());
    }
}

std::string StayAliveSystem::getName() {
    return "StayAliveSystem";
}
