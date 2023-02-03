//
// Created by gugue on 31/01/2023.
//

#include <iostream>
#include "ProjectileHitboxSystem.h"
#include "Engine/Engine.h"
#include "Engine/EntityUtils.h"
#include "Hitbox.h"

void ProjectileHitboxSystem::update(EnginePtr engine) {
    std::unordered_map<size_t, std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>>>> teams;
    std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>, size_t>> colliders;
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
                    entity->getComponent<ColliderComponent>()->onCollision(engine, entity, otherEntity, teams);
                    break;
                }
            }
        }
    }
}

std::string ProjectileHitboxSystem::getName() {
    return "ProjectileHitboxSystem";
}
