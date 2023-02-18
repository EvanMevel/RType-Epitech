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
#include "Engine/Network/Packets/EntityInfoPacket.h"
#include "Engine/Component/CooldownComponent.h"
#include "Levels.h"
#include "Engine/engineLua/LuaEntityTypeFactory.h"
#include "Engine/Component/IAComponent.h"

const std::string enemies[] = {
    "enemy1",
    "enemy2"
};

EnemyRandomSpawnSystem::EnemyRandomSpawnSystem() : gen(rd()), distrx(0, 400), distry(0, 750) {
    int enemyCount = sizeof(enemies) / sizeof(enemies[0]);
    distrType = std::uniform_int_distribution<int>(0, enemyCount - 1);
}

void EnemyRandomSpawnSystem::spawnRandomEntity(std::unique_ptr<Engine> &engine, RTypeServerPtr srv) {
    auto ent = engine->getScene()->createEntity();
    int x = 1300 + distrx(gen);
    int y = 50 + distry(gen);
    ent->addComponent<PositionComponent>(x, y);

    std::string enemy = enemies[distrType(gen)];
    auto typeFactory = engine->getModule<LuaEntityTypeFactory>();
    typeFactory->initEntity(ent, enemy);

    EntityInfoPacket newEntityPacket(ent);
    srv->broadcast(newEntityPacket);
}

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
    size_t enemyCount = 0;

    std::function<void(std::shared_ptr<Entity>)> countEnemies = [&enemyCount](std::shared_ptr<Entity> ent) {
        auto ia = ent->getComponent<IAComponent>();
        if (ia) {
            enemyCount++;
        }
    };
    engine->getScene()->forEachEntity(countEnemies);
    if (enemyCount < levels->enemyCount) {
        levels->enemyDead++;
        levels->enemyCount = 1 + (levels->enemyDead / 2);
    } else {
        return;
    }
    while (enemyCount < levels->enemyCount) {
        spawnRandomEntity(engine, srv);
        enemyCount++;
    }
}
