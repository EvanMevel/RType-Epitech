//
// Created by evans on 01/02/2023.
//

#include "EnemyRandomSpawnSystem.h"
#include "Engine/EntityUtils.h"
#include "RTypeServer.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"

void EnemyRandomSpawnSystem::update(std::unique_ptr<Engine> &engine) {
    count = (count + 1) % 20;
    if (count != 0) {
        return;
    }
    RTypeServerPtr srv = engine->getModule<RTypeServer>();
    size_t enemies = 0;
    for (auto &ent : engine->getScene()->getEntities()) {
        auto type = ent->getComponent<EntityTypeComponent>();
        if (type && type->getType() == EntityType::ENEMY) {
            enemies++;
        }
    }
    while (enemies < srv->getClients().size()) {
        auto ent = engine->getScene()->createEntity();
        int x = 400;
        int y = distr(gen);
        entity::initEnemy(ent, x, y);
        enemies++;

        EntityInfoPacket newEntityPacket(ent);
        srv->broadcast(newEntityPacket);
    }
}

EnemyRandomSpawnSystem::EnemyRandomSpawnSystem() : gen(rd()), distr(0, 400) {}
