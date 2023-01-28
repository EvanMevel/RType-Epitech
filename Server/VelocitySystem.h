//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_VELOCITYSYSTEM_H
#define R_TYPE_SERVER_VELOCITYSYSTEM_H

#include "RTypeServer.h"
#include "Engine/ISystem.h"

class VelocitySystem : public ISystem {

public:
    RTypeServerPtr srv;
    int count = 0;

    explicit VelocitySystem(RTypeServerPtr srv) : srv(srv) {}

    void update(Engine &engine) override;
};


#endif //R_TYPE_SERVER_VELOCITYSYSTEM_H
