//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_STAYALIVESYSTEM_H
#define R_TYPE_SERVER_STAYALIVESYSTEM_H

#include "Engine/ISystem.h"
#include "Client/ClientNetServer.h"


class StayAliveSystem : public ISystem {
private:
    long long lastPing = 0;
    void update(Engine &engine) override;

    std::string getName() override;
};


#endif //R_TYPE_SERVER_STAYALIVESYSTEM_H
