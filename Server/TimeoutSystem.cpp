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
        if (data->getLastPing() + RTYPE_TIMEOUT < currentTime) {
            std::cout << "Client " << client->addressPort() << " timed out" << std::endl;
            it = server.getClients().erase(it);
        } else {
            it++;
        }
    }
}

TimeoutSystem::TimeoutSystem(RTypeServer &server) : server(server) {}
