//
// Created by evans on 28/01/2023.
//

#include <iostream>
#include "VelocitySystem.h"
#include "Engine/Engine.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/AccelerationPhysicComponent.h"

void VelocitySystem::update(Engine &engine) {
    count = (count + 1) % 4;
    for (auto &entity: engine.getScene()->getEntities()) {
        auto pos = entity->getComponent<PositionComponent>();
        auto physic = entity->getComponent<AccelerationPhysicComponent>();
        if (pos != nullptr && physic != nullptr) {
            if (physic->acceleration.lengthSquare() != 0) {
                // Add acceleration to velocity
                physic->velocity.x += physic->acceleration.x;
                physic->velocity.y += physic->acceleration.y;

                // Decrement acceleration
                physic->acceleration.decrementTo0(physic->accelerationSlow);
            }

            if (physic->velocity.lengthSquare() == 0) {
                continue;
            }

            if (physic->maxVelocity != 0) {
                physic->velocity.ensureNotGreater((int) physic->maxVelocity);
            }

            //std::cout << "Accel: " << physic->acceleration.x << ", " << physic->acceleration.y << " Vel: " << physic->velocity.x << ", " << physic->velocity.y << std::endl;

            // Add velocity to position
            pos->x += physic->velocity.x;
            pos->y += physic->velocity.y;

            // Decrement velocity
            physic->velocity.decrementTo0(physic->velocitySlow);

            if (count == 0) {
                entityMoved(engine, entity);
            }
        }
    }
}

void VelocitySystem::entityMoved(Engine &engine, std::shared_ptr<Entity> entity) {

}

std::string VelocitySystem::getName() {
    return "VelocitySystem";
}
