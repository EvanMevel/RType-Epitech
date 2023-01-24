//
// Created by evans on 24/01/2023.
//

#include "TimeoutSystem.h"
#include "Engine/TimeUtil.h"


void TimeoutSystem::update(Engine &engine) {
    long long currentTime = getCurrentTime();
    auto it = server.getClients().begin();
    while (it != server.getClients().end()) {
        auto &client = it->second.first;
        auto &data = it->second.second;
        std::cout << "time: " << (data.getLastPing() + RTYPE_TIMEOUT) - currentTime << std::endl;
        if (data.getLastPing() + RTYPE_TIMEOUT < currentTime) {
            std::cout << "Client " << client->getAddress() << ":" << client->getPort() << " timed out" << std::endl;
            it = server.getClients().erase(it);
        } else {
            it++;
        }
    }
}

TimeoutSystem::TimeoutSystem(RTypeServer &server) : server(server) {}
