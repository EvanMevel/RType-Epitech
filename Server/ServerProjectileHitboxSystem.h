//
// Created by gugue on 31/01/2023.
//

#ifndef R_TYPE_SERVER_SERVERPROJECTILEHITBOXSYSTEM_H
#define R_TYPE_SERVER_SERVERPROJECTILEHITBOXSYSTEM_H

#include "RTypeServer.h"
#include "Engine/ISystem.h"
#include "Engine/Entity.h"
#include "Engine/ProjectileHitboxSystem.h"

class ServerProjectileHitboxSystem : public ProjectileHitboxSystem {
public:
    std::string getName() override;
};

#endif //R_TYPE_SERVER_SERVERPROJECTILEHITBOXSYSTEM_H
