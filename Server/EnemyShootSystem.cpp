//
// Created by evans on 01/02/2023.
//

#include "EnemyShootSystem.h"
#include "Engine/Engine.h"
#include "Engine/EntityUtils.h"
#include "CooldownComponent.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"
#include "RTypeServer.h"

void EnemyShootSystem::update(std::unique_ptr<Engine> &engine) {
    auto lock = engine->getScene()->obtainLock();
    auto &entities = engine->getScene()->getEntities();
    for (size_t i = 0; i < entities.size(); i++) {
        auto &ent = entities[i];
        auto type = ent->getComponent<EntityTypeComponent>();
        if (type && type->getType() == EntityType::ENEMY) {
            auto cd = ent->getComponent<CooldownComponent>();
            auto pos = ent->getComponent<PositionComponent>();
            if (cd == nullptr || pos == nullptr) {
                continue;
            }
            cd->current++;
            if (cd->current >= cd->cooldown) {
                cd->current = 0;
                auto projectile = engine->getScene()->unsafeCreateEntity();
                entity::initProjectile(projectile, pos->x, pos->y + 20, -5);

                auto team = projectile->addComponent<TeamComponent>();
                team->setTeam(1);

                EntityInfoPacket newEntityPacket(projectile);
                engine->getModule<RTypeServer>()->broadcast(newEntityPacket);
            }
        }
    }
}
