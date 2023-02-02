//
// Created by gugue on 31/01/2023.
//

#include <iostream>
#include "ProjectileHitboxSystem.h"
#include "Engine/Engine.h"
#include "Engine/Component/HitboxComponent.h"
#include "Engine/Component/TeamComponent.h"
#include "Engine/Component/PositionComponent.h"

void ProjectileHitboxSystem::update(EnginePtr engine) {
    count = (count + 1) % 4;
    for (auto &entity: engine->getScene()->getEntities()) {
        auto hitbox = entity->getComponent<HitboxComponent>();
        auto team = entity->getComponent<TeamComponent>();
        auto pos = entity->getComponent<PositionComponent>();

        if (hitbox != nullptr && team != nullptr && pos != nullptr) {
            for (auto &ent: engine->getScene()->getEntities()) {
                auto tmpPos = ent->getComponent<PositionComponent>();
                auto tmpHitbox = ent->getComponent<HitboxComponent>();
                auto tmpTeam = ent->getComponent<TeamComponent>();
                if (tmpHitbox != nullptr && tmpTeam != nullptr && tmpPos != nullptr) {
                    if (team->getTeam() == tmpTeam->getTeam())
                        continue;
                    int tmpPosX = tmpPos->x + static_cast<int>(tmpHitbox->getLengthX());
                    int PosX = pos->x + static_cast<int>(hitbox->getLengthX());

                    int tmpPosY = tmpPos->y + static_cast<int>(tmpHitbox->getLengthY());
                    int PosY = pos->y + static_cast<int>(hitbox->getLengthY());

                    if (pos->x < tmpPosX && PosX > tmpPos->x   &&   pos->y < tmpPosY && PosY > tmpPos->y)
                        std::cout << "Collision detected !" << std::endl;
                }
            }
        }
    }
}

std::string ProjectileHitboxSystem::getName() {
    return "ProjectileHitboxSystem";
}
