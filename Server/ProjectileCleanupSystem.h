//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_PROJECTILECLEANUPSYSTEM_H
#define R_TYPE_SERVER_PROJECTILECLEANUPSYSTEM_H

#include "Engine/ISystem.h"
#include "RTypeServer.h"

class ProjectileCleanupSystem : public ISystem {
private:
    RTypeServerPtr server;

public:
    explicit ProjectileCleanupSystem(const RTypeServerPtr &server);

    void update(Engine &engine) override;
};


#endif //R_TYPE_SERVER_PROJECTILECLEANUPSYSTEM_H
