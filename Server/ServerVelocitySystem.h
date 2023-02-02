//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_SERVERVELOCITYSYSTEM_H
#define R_TYPE_SERVER_SERVERVELOCITYSYSTEM_H

#include "Engine/VelocitySystem.h"

class ServerVelocitySystem : public VelocitySystem {
public:
    ServerVelocitySystem();

    void entityMoved(EnginePtr engine, std::shared_ptr<Entity> entity) override;

    std::string getName() override;
};


#endif //R_TYPE_SERVER_SERVERVELOCITYSYSTEM_H
