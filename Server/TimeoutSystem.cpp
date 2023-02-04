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

    long long currentTime = getCurrentTime();

    std::function<bool(std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> &data)> func = [server, currentTime](std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> &data) {
        if (data->getLastPing() + RTYPE_TIMEOUT < currentTime) {
            log() << "Client " << client->addressPort() << " timed out" << std::endl;
            server->clientDisconnected(client, data);
            return true;
        }
        return false;
    };

    server->filterClients(func);
}

std::string TimeoutSystem::getName() {
    return "TimeoutSystem";
}
