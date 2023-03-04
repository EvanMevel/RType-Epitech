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
#include "InanimateComponent.h"
#include "ColliderComponent.h"
#include "Hitbox.h"
#include "EntityTypeComponent2.h"

void VelocitySystem::applyVelocity(EnginePtr engine, std::shared_ptr<Entity> entity, std::shared_ptr<PositionComponent> pos,
                                   std::shared_ptr<PhysicComponent> physic,
                                   std::vector<std::pair<std::shared_ptr<Entity>, Hitbox>> inanimates) {



    // Add velocity to position
    pos->x += physic->velocity.x;
    pos->y += physic->velocity.y;

    // Apply hitbox collision
    auto hitboxComp = entity->getComponent<HitboxComponent>();

    if (hitboxComp != nullptr && !entity->hasComponent<ColliderComponent>() && !entity->hasComponent<InanimateComponent>()) {
        auto hitbox = Hitbox(pos, hitboxComp);

        for (auto &inanimate: inanimates) {
            if (hitbox.isColliding(inanimate.second)) {
                pos->x -= physic->velocity.x;
                pos->y -= physic->velocity.y;

                physic->velocity.x = 0;
                physic->velocity.y = 0;
                physic->acceleration.x = 0;
                physic->acceleration.y = 0;
                break;
            }
        }
    }

    auto type = entity->getComponent<EntityTypeComponent2>();

    if (type != nullptr && type->getEntityType() == "player") {
        if (pos->x <= 0 || pos->y <= 0 || pos->y + hitboxComp->getHeight() >= 1000 ||
            pos->x + hitboxComp->getWidth() >= 1820) {
            pos->x -= physic->velocity.x;
            pos->y -= physic->velocity.y;

            physic->velocity.x = 0;
            physic->velocity.y = 0;
            physic->acceleration.x = 0;
            physic->acceleration.y = 0;
        }
    }

    // Decrement velocity
    physic->velocity.decrementTo0(physic->velocitySlow);
}

bool VelocitySystem::applyPhysic(EnginePtr engine, std::shared_ptr<Entity> entity,
                                 std::vector<std::pair<std::shared_ptr<Entity>, Hitbox>> inanimates) {
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

        applyVelocity(engine, entity, pos, physic, inanimates);

        return true;
    }
    return false;
}

void VelocitySystem::update(EnginePtr engine) {
    std::vector<std::pair<std::shared_ptr<Entity>, Hitbox>> inanimates;
    auto lock = engine->getScene()->obtainLock();
    for (auto &entity: engine->getScene()->getEntities()) {
        auto hitboxComp = entity->getComponent<HitboxComponent>();
        auto pos = entity->getComponent<PositionComponent>();
        if (entity->hasComponent<InanimateComponent>() && hitboxComp != nullptr && pos != nullptr) {
            auto hitbox = Hitbox(pos, hitboxComp);
            inanimates.emplace_back(entity, hitbox);
        }
    }
    for (auto &entity : engine->getScene()->getEntities()) {
        if (applyPhysic(engine, entity, inanimates)) {
            entityMoved(engine, entity);
        }
    }
}

void VelocitySystem::entityMoved(EnginePtr engine, std::shared_ptr<Entity> entity) {

}

std::string VelocitySystem::getName() {
    return "VelocitySystem";
}
