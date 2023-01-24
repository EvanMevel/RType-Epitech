//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_TIMEOUTSYSTEM_H
#define R_TYPE_SERVER_TIMEOUTSYSTEM_H

#define RTYPE_TIMEOUT 5000

#include "Engine/ISystem.h"
#include "RTypeServer.h"

class TimeoutSystem : public ISystem {
private:
    RTypeServer &server;
public:
    explicit TimeoutSystem(RTypeServer &server);

public:
    void update(Engine &engine) override;
};


#endif //R_TYPE_SERVER_TIMEOUTSYSTEM_H
