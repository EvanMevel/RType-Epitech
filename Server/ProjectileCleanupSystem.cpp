//
// Created by evans on 31/01/2023.
//

#include "ProjectileCleanupSystem.h"
#include "RTypeServer.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Network/Packets/EntityDestroyPacket.h"

void ProjectileCleanupSystem::update(Engine &engine) {
    auto it = engine.getScene()->getEntities().begin();
    while (it != engine.getScene()->getEntities().end()) {
        auto &entity = *it;
        auto type = entity->getComponent<EntityTypeComponent>();
        if (type == nullptr || type->getType() != EntityType::PROJECTILE) {
            it++;
            continue;
        }
        auto pos = entity->getComponent<PositionComponent>();
        if (pos == nullptr) {
            it++;
            continue;
        }
        if (pos->getX() < -20 || pos->getX() > 200) {
            EntityDestroyPacket packet(entity->getId());
            engine.getModule<RTypeServer>()->broadcast(packet);
            it = engine.getScene()->getEntities().erase(it);
        } else {
            it++;
        }
    }
}

ProjectileCleanupSystem::ProjectileCleanupSystem() {}
