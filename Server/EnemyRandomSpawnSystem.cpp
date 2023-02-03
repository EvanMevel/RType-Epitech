//
// Created by evans on 01/02/2023.
//

#include "EnemyRandomSpawnSystem.h"
#include "Engine/EntityUtils.h"
#include "RTypeServer.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"
#include "CooldownComponent.h"

void EnemyRandomSpawnSystem::update(std::unique_ptr<Engine> &engine) {
    count = (count + 1) % ENGINE_TPS;
    if (count != 0) {
        return;
    }
    RTypeServerPtr srv = engine->getModule<RTypeServer>();
    size_t enemies = 0;

    std::function<void(std::shared_ptr<Entity>)> countEnemies = [&enemies](std::shared_ptr<Entity> ent) {
        auto type = ent->getComponent<EntityTypeComponent>();
        if (type && type->getType() == EntityType::ENEMY) {
            enemies++;
        }
    };
    engine->getScene()->forEachEntity(countEnemies);
    while (enemies < srv->getClientCount()) {
        auto ent = engine->getScene()->createEntity();
        int x = 400;
        int y = distr(gen);
        entity::initEnemy(ent, x, y);

        auto cd = ent->addComponent<CooldownComponent>();
        cd->cooldown = ENGINE_TPS * 2;
        enemies++;

        EntityInfoPacket newEntityPacket(ent);
        srv->broadcast(newEntityPacket);
    }
}

EnemyRandomSpawnSystem::EnemyRandomSpawnSystem() : gen(rd()), distr(0, 400) {}
