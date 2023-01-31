//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_VELOCITYSYSTEM_H
#define R_TYPE_SERVER_VELOCITYSYSTEM_H

#include "Engine/ISystem.h"
#include "Engine/Entity.h"

class VelocitySystem : public ISystem {

public:
    int count = 0;

    void update(Engine &engine) override;

    virtual void entityMoved(Engine &engine, std::shared_ptr<Entity> entity);

    std::string getName() override;
};


#endif //R_TYPE_SERVER_VELOCITYSYSTEM_H
