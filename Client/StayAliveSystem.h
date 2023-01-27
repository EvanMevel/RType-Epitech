//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_STAYALIVESYSTEM_H
#define R_TYPE_SERVER_STAYALIVESYSTEM_H

#include "Engine/ISystem.h"
#include "Engine/Network/NetworkRemoteServer.h"


class StayAliveSystem : public ISystem {
private:
    NetworkRemoteServer<Engine&> &server;
    long long lastPing = 0;
public:
    explicit StayAliveSystem(NetworkRemoteServer<Engine &> &server);

public:
    void update(Engine &engine) override;

};


#endif //R_TYPE_SERVER_STAYALIVESYSTEM_H