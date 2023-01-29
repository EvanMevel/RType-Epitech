//
// Created by evans on 28/01/2023.
//

#include <iostream>
#include "VelocitySystem.h"
#include "Engine/Engine.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/VelocityComponent.h"
#include "Engine/Component/AccelerationComponent.h"
#include "MaxVelocityComponent.h"

void VelocitySystem::update(Engine &engine) {
    count = (count + 1) % 4;
    for (auto &entity: engine.getScene()->getEntities()) {
        auto pos = entity->getComponent<PositionComponent>();
        auto vel = entity->getComponent<VelocityComponent>();
        auto accel = entity->getComponent<AccelerationComponent>();
        if (pos != nullptr && vel != nullptr && accel != nullptr) {
            if (accel->lengthSquare() != 0) {
                // Add acceleration to velocity
                vel->x += accel->x;
                vel->y += accel->y;

                // Decrement acceleration
                accel->decrementTo0(1);
            }

            if (vel->lengthSquare() == 0) {
                continue;
            }

            auto maxVelo = entity->getComponent<MaxVelocityComponent>();
            if (maxVelo != nullptr) {
                vel->ensureNotGreater((int) maxVelo->getMaxVelocity());
            }

            std::cout << "Accel: " << accel->x << ", " << accel->y << " Vel: " << vel->x << ", " << vel->y << std::endl;

            // Add velocity to position
            pos->x += vel->x;
            pos->y += vel->y;

            // Decrement velocity
            vel->decrementTo0(1);

            if (count == 0) {
                entityMoved(entity);
            }
        }
    }
}

void VelocitySystem::entityMoved(std::shared_ptr<Entity> entity) {

}

std::string VelocitySystem::getName() {
    return "VelocitySystem";
}
