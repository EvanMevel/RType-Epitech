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

#include "EnemyRandomSpawnSystem.h"
#include "Engine/EntityUtils.h"
#include "RTypeServer.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"
#include "CooldownComponent.h"
#include "EnemyInfoComponent.h"
#include "Levels.h"

EnemyRandomSpawnSystem::EnemyRandomSpawnSystem() : gen(rd()), distrx(0, 400), distry(0, 750), distrType(0, 1) {}

void EnemyRandomSpawnSystem::update(std::unique_ptr<Engine> &engine) {
    auto levels = engine->getModule<Levels>();
    if (levels == nullptr) {
        return;
    }
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
    if (enemies < levels->enemyCount) {
        levels->enemyDead++;
        levels->enemyCount = 1 + (levels->enemyDead / 2);
    } else {
        return;
    }
    while (enemies < levels->enemyCount) {

        auto ent = engine->getScene()->createEntity();
        int x = 1300 + distrx(gen);
        int y = 50 + distry(gen);
        entity::initEnemy(ent, x, y);

        EnemyType type = static_cast<EnemyType>(distrType(gen));
        auto enemyInfo = ent->addComponent<EnemyInfoComponent>();
        enemyInfo->type = type;

        auto cd = ent->addComponent<CooldownComponent>();

        if (type == EnemyType::BASIC) {
            cd->cooldown = ENGINE_TPS * 2;
        } else if (type == EnemyType::FAST) {
            cd->cooldown = ENGINE_TPS * 1.2;
            ent->getComponent<HitboxComponent>()->setHeight(32 * 3);
        }

        enemies++;

        EntityInfoPacket newEntityPacket(ent);
        srv->broadcast(newEntityPacket);
    }
}
