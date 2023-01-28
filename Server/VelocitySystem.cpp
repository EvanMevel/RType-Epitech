//
// Created by evans on 28/01/2023.
//

#include "VelocitySystem.h"
#include "Engine/Engine.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/VelocityComponent.h"
#include "Engine/Component/AccelerationComponent.h"

void VelocitySystem::update(Engine &engine) {
    count = (count + 1) % 4;
    if (count != 0) {
        return;
    }
    for (auto &entity: engine.getScene()->getEntities()) {
        auto pos = entity->getOrCreate<PositionComponent>();
        auto vel = entity->getOrCreate<VelocityComponent>();
        auto accel = entity->getOrCreate<AccelerationComponent>();
        if (pos != nullptr && vel != nullptr && accel != nullptr) {

            // Add acceleration to velocity
            vel->x += accel->x;
            vel->y += accel->y;

            // Add velocity to position
            pos->x += vel->x;
            pos->y += vel->y;

            // Decrement acceleration
            accel->decrementTo0(1);

            // Decrement velocity
            vel->decrementTo0(1);

            EntityVelocityPacket packet((int) entity->getId(), pos->clone(), vel->clone(), accel->clone());
            srv->broadcast(packet);
        }
    }
}
