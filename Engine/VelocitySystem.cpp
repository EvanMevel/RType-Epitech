//
// Created by evans on 28/01/2023.
//

#include <iostream>
#include "VelocitySystem.h"
#include "Engine/EntityUtils.h"

void VelocitySystem::update(EnginePtr engine) {
    count = (count + 1) % 4;
    auto lock = engine->getScene()->obtainLock();
    for (auto &entity: engine->getScene()->getEntities()) {
        if (entity::applyPhysic(entity)) {
            entityMoved(engine, entity);
        }
    }
}

void VelocitySystem::entityMoved(EnginePtr engine, std::shared_ptr<Entity> entity) {

}

std::string VelocitySystem::getName() {
    return "VelocitySystem";
}
