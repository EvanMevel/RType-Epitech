//
// Created by evans on 24/01/2023.
//

#include "TimeoutSystem.h"
#include "Engine/TimeUtil.h"
#include "RTypeServer.h"

TimeoutSystem::TimeoutSystem() {

}

void TimeoutSystem::update(EnginePtr engine) {
    auto server = engine->getModule<RTypeServer>();
    auto it = server->getClients().begin();

    long long currentTime = getCurrentTime();
    while (it != server->getClients().end()) {
        auto &client = it->second.first;
        auto &data = it->second.second;
        if (data->getLastPing() + RTYPE_TIMEOUT < currentTime) {
            std::cout << "Client " << client->addressPort() << " timed out" << std::endl;
            it = server->getClients().erase(it);
        } else {
            it++;
        }
    }
}

std::string TimeoutSystem::getName() {
    return "TimeoutSystem";
}
