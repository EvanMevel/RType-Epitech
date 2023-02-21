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

#include "EntityUtils.h"
#include "Engine/Component/PhysicComponent.h"
#include "Engine/Component/TeamComponent.h"
#include "Engine/Component/HealthComponent.h"
#include "EntityTypeComponent2.h"

void entityDied(EnginePtr engine, std::shared_ptr<Entity> entity, std::shared_ptr<Entity> cause) {
    engine->getScene()->removeEntity(entity);
}

void entity::projectileHit(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other,
                   std::unordered_map<size_t, std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>>>> &teams,
                   std::function<void(EnginePtr engine, std::shared_ptr<Entity> touched, int damages)> onDamage) {
    auto health = other->getComponent<HealthComponent>();
    if (health != nullptr) {
        if (!health->isInvincible()) {
            health->damage(10);
            if (!health->isAlive()) {
                entityDied(engine, other, self);
                auto team = teams[other->getComponent<TeamComponent>()->getTeam()];
                team.erase(std::remove_if(team.begin(), team.end(),
                                          [other](std::tuple<Hitbox, std::shared_ptr<Entity>> &t) {
                                              return std::get<1>(t)->getId() == other->getId();
                                          }), team.end());
            } else {
                onDamage(engine, other, 10);
            }
        }
    } else {
        auto type = other->getComponent<EntityTypeComponent2>();
        if (type != nullptr && type->getEntityType() == "projectile") {
            entityDied(engine, other, self);
            auto team = teams[other->getComponent<TeamComponent>()->getTeam()];
            team.erase(std::remove_if(team.begin(), team.end(), [other](std::tuple<Hitbox, std::shared_ptr<Entity>> &t) {
                return std::get<1>(t)->getId() == other->getId();
            }), team.end());
        }
    }
    entityDied(engine, self, other);
}

bool entity::applyPhysic(std::shared_ptr<Entity> entity) {
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

        //std::cout << "Accel: " << physic->acceleration.x << ", " << physic->acceleration.y << " Vel: " << physic->velocity.x << ", " << physic->velocity.y << std::endl;

        // Add velocity to position
        pos->x += physic->velocity.x;
        pos->y += physic->velocity.y;

        // Decrement velocity
        physic->velocity.decrementTo0(physic->velocitySlow);

        return true;
    }
    return false;
}