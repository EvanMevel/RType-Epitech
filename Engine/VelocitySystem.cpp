// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>
#include "VelocitySystem.h"
#include "Engine/Engine.h"

void VelocitySystem::applyVelocity(std::shared_ptr<Entity> entity, std::shared_ptr<PositionComponent> pos, std::shared_ptr<PhysicComponent> physic) {

    // Add velocity to position
    pos->x += physic->velocity.x;
    pos->y += physic->velocity.y;

    // Decrement velocity
    physic->velocity.decrementTo0(physic->velocitySlow);
}

bool VelocitySystem::applyPhysic(std::shared_ptr<Entity> entity) {
    auto pos = entity->getComponent<PositionComponent>();
    auto physic = entity->getComponent<PhysicComponent>();
    if (pos != nullptr && physic != nullptr) {
        if (physic->acceleration.lengthSquare() != 0) {
            // Add acceleration to velocity
            physic->velocity.x += physic->acceleration.x;
            physic->velocity.y += physic->acceleration.y;

            // Decrement acceleration
            physic->acceleration.decrementTo0(physic->accelerationSlow);
        }

        if (physic->velocity.lengthSquare() == 0) {
            return false;
        }

        if (physic->maxVelocity != 0) {
            physic->velocity.ensureNotGreater((int) physic->maxVelocity);
        }

        applyVelocity(entity, pos, physic);

        return true;
    }
    return false;
}

void VelocitySystem::update(EnginePtr engine) {
    count = (count + 1) % 4;
    auto lock = engine->getScene()->obtainLock();
    for (auto &entity: engine->getScene()->getEntities()) {
        if (applyPhysic(entity)) {
            entityMoved(engine, entity);
        }
    }
}

void VelocitySystem::entityMoved(EnginePtr engine, std::shared_ptr<Entity> entity) {

}

std::string VelocitySystem::getName() {
    return "VelocitySystem";
}
