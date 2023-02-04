//
// Created by gugue on 31/01/2023.
//

#ifndef R_TYPE_SERVER_PROJECTILEHITBOXSYSTEM_H
#define R_TYPE_SERVER_PROJECTILEHITBOXSYSTEM_H

#include "Engine/ISystem.h"
#include "Engine/Entity.h"

class ProjectileHitboxSystem : public ISystem {

public:
    void update(EnginePtr engine) override;

    std::string getName() override;
};


#endif //R_TYPE_SERVER_PROJECTILEHITBOXSYSTEM_H
