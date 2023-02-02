//
// Created by gugue on 31/01/2023.
//

#include <iostream>
#include "ProjectileHitboxSystem.h"
#include "Engine/Engine.h"
#include "Engine/Component/HitboxComponent.h"
#include "Engine/Component/TeamComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "Hitbox.h"

void ProjectileHitboxSystem::update(EnginePtr engine) {
    for (auto &entity: engine->getScene()->getEntities()) {
        auto hitboxComp = entity->getComponent<HitboxComponent>();
        auto team = entity->getComponent<TeamComponent>();
        auto pos = entity->getComponent<PositionComponent>();

        if (hitboxComp != nullptr && team != nullptr && pos != nullptr) {

            auto hitbox = Hitbox(pos, hitboxComp);

            for (auto &ent: engine->getScene()->getEntities()) {
                auto tmpPos = ent->getComponent<PositionComponent>();
                auto tmpHitbox = ent->getComponent<HitboxComponent>();
                auto tmpTeam = ent->getComponent<TeamComponent>();
                if (tmpHitbox != nullptr && tmpTeam != nullptr && tmpPos != nullptr) {
                    if (team->getTeam() == tmpTeam->getTeam())
                        continue;
                    auto otherHitbox = Hitbox(tmpPos, tmpHitbox);
                    if (hitbox.isColliding(otherHitbox))
                        std::cout << "Collision detected !" << std::endl;
                }
            }
        }
    }
}

std::string ProjectileHitboxSystem::getName() {
    return "ProjectileHitboxSystem";
}
