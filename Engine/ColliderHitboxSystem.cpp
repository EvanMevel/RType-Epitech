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

#include "ColliderHitboxSystem.h"
#include <utility>
#include "Engine/Engine.h"
#include "Hitbox.h"
#include "ColliderComponent.h"
#include "EntityTypeComponent.h"

ColliderHitboxSystem::ColliderHitboxSystem() {
}

void ColliderHitboxSystem::update(EnginePtr engine) {
    std::vector<std::pair<std::shared_ptr<Entity>, Hitbox>> colliders;
    std::vector<std::pair<std::shared_ptr<Entity>, Hitbox>> hitboxes;

    {
        auto lock = engine->getScene()->obtainLock();
        for (auto &entity: engine->getScene()->getEntities()) {
            auto hitboxComp = entity->getComponent<HitboxComponent>();
            auto pos = entity->getComponent<PositionComponent>();

            if (hitboxComp != nullptr && pos != nullptr) {
                auto hitbox = Hitbox(pos, hitboxComp);
                hitboxes.emplace_back(entity, hitbox);
                if (entity->hasComponent<ColliderComponent>()) {
                    colliders.emplace_back(entity, hitbox);
                }
            }
        }
    }

    if (colliders.empty() || hitboxes.empty()) {
        return;
    }

    CollideResult res;
    for (auto &collider: colliders) {
        res = CollideResult::NONE;
        auto other = hitboxes.begin();
        while (other != hitboxes.end()) {
            if (collider.first == other->first) {
                ++other;
                continue;
            }
            if (collider.second.isColliding(other->second)) {
                res = collider.first->getComponent<ColliderComponent>()->onCollision(engine, collider.first, other->first);

                if (res & CollideResult::TARGET_REMOVED) {
                    other = hitboxes.erase(other);
                    if (res & CollideResult::SOURCE_REMOVED) {
                        break;
                    }
                    continue;
                } else if (res & CollideResult::SOURCE_REMOVED) {
                    break;
                }
            }
            ++other;
        }
        if (res & CollideResult::SOURCE_REMOVED) {
            std::remove_if(hitboxes.begin(), hitboxes.end(), [&collider](const std::pair<std::shared_ptr<Entity>, Hitbox> &pair) {
                return pair.first == collider.first;
            });
            break;
        }
    }
}

std::string ColliderHitboxSystem::getName() {
    return "ProjectileHitboxSystem";
}
