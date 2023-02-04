//
// Created by evans on 31/01/2023.
//

#include "ProjectileCleanupSystem.h"
#include "RTypeServer.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Network/Packets/EntityDestroyPacket.h"

void ProjectileCleanupSystem::update(EnginePtr engine) {
    std::function<bool(std::shared_ptr<Entity> entity, EnginePtr engine)> f = [](std::shared_ptr<Entity> entity, EnginePtr engine) {
        auto type = entity->getComponent<EntityTypeComponent>();
        if (type == nullptr || type->getType() != EntityType::PROJECTILE) {
            return false;
        }
        auto pos = entity->getComponent<PositionComponent>();
        if (pos == nullptr) {
            return false;
        }
        if (pos->getX() < -20 || pos->getX() > 600) {
            EntityDestroyPacket packet(entity->getId());
            engine->getModule<RTypeServer>()->broadcast(packet);
            return true;
        }
        return false;
    };

    engine->getScene()->filterEntities(f, engine);
}

ProjectileCleanupSystem::ProjectileCleanupSystem() {}
