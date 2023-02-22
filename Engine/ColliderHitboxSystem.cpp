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
#include "Engine/EntityUtils.h"
#include "Hitbox.h"
#include "TeamComponent.h"
#include "ColliderComponent.h"
#include "EntityTypeComponent2.h"

void ColliderHitboxSystem::update(EnginePtr engine) {
    std::unordered_map<size_t, std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>>>> teams;
    std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>, size_t>> colliders;
    {
        auto lock = engine->getScene()->obtainLock();
        for (auto &entity: engine->getScene()->getEntities()) {
            auto hitboxComp = entity->getComponent<HitboxComponent>();
            auto team = entity->getComponent<TeamComponent>();
            auto pos = entity->getComponent<PositionComponent>();

            if (hitboxComp != nullptr && team != nullptr && pos != nullptr) {
                auto hitbox = Hitbox(pos, hitboxComp);

                std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>>> &v = teams[team->getTeam()];

                v.emplace_back(hitbox, entity);
                if (entity->hasComponent<ColliderComponent>()) {
                    colliders.emplace_back(hitbox, entity, team->getTeam());
                }
            }
        }
    }
    if (teams.size() < 2 || colliders.empty()) {
        return;
    }

    /*std::cout << "Collision check" << std::endl;
    for (auto hitboxTeam: hitboxes) {
        std::cout << "Team " << hitboxTeam.first << std::endl;
        for (auto &hitbox: hitboxTeam.second) {
            std::cout << "Hitbox " << std::get<1>(hitbox)->getId() << std::endl;
        }
    }
    std::cout << "Colliders" << std::endl;
    for (auto &collider: colliders) {
        std::cout << "Collider " << std::get<1>(collider)->getId() << std::endl;
    }*/

    for (auto &collider: colliders) {
        auto hitbox = std::get<0>(collider);
        auto entity = std::get<1>(collider);
        auto teamId = std::get<2>(collider);

        for (auto team: teams) {
            if (team.first == teamId) {
                continue;
            }
            for (auto &otherTeamHitbox: team.second) {
                auto otherHitbox = std::get<0>(otherTeamHitbox);
                auto otherEntity = std::get<1>(otherTeamHitbox);
                if (hitbox.isColliding(otherHitbox)) {
                    entity->getComponent<ColliderComponent>()->onCollision(engine, entity, otherEntity, teams, _onDamage);
                    break;
                }
            }
        }
    }
}

std::string ColliderHitboxSystem::getName() {
    return "ProjectileHitboxSystem";
}

ColliderHitboxSystem::ColliderHitboxSystem(std::function<void(EnginePtr engine, std::shared_ptr<Entity> touched, int damages)> onDamage): _onDamage(std::move(onDamage)) {
}
