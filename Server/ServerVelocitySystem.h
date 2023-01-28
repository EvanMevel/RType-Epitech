//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_SERVERVELOCITYSYSTEM_H
#define R_TYPE_SERVER_SERVERVELOCITYSYSTEM_H

#include "RTypeServer.h"
#include "Engine/ISystem.h"
#include "Engine/Entity.h"
#include "Engine/VelocitySystem.h"

class ServerVelocitySystem : public VelocitySystem {
public:
    RTypeServerPtr srv;

    explicit ServerVelocitySystem(RTypeServerPtr srv) : srv(srv) {}

    void entityMoved(std::shared_ptr<Entity> entity) override;

    std::string getName() override;
};


#endif //R_TYPE_SERVER_SERVERVELOCITYSYSTEM_H
