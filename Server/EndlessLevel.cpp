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

#include "EndlessLevel.h"
#include "Engine/Component/IAComponent.h"

const std::string enemies[] = {
        "enemy1",
        "enemy2"
};

EndlessLevel::EndlessLevel() : Level("Endless"), gen(rd()), distry(0, 750) {
    int typeSize = sizeof(enemies) / sizeof(enemies[0]);
    distrType = std::uniform_int_distribution<int>(0, typeSize - 1);
}

void EndlessLevel::spawnRandomEntity(std::unique_ptr<Engine> &engine, RTypeServerPtr srv) {
    int x = 1800;
    int y = 50 + distry(gen);

    std::string enemyType = enemies[distrType(gen)];

    engine->getScene()->createEntity(engine, enemyType, x, y);
}

bool EndlessLevel::update(int x, std::unique_ptr<Engine> &engine) {
    count = (count + 1) % ENGINE_TPS;
    if (count != 0) {
        return false;
    }
    RTypeServerPtr srv = engine->getModule<RTypeServer>();
    size_t eCount = 0;

    std::function<void(std::shared_ptr<Entity>)> countEnemies = [&eCount](std::shared_ptr<Entity> ent) {
        auto ia = ent->getComponent<IAComponent>();
        if (ia) {
            eCount++;
        }
    };
    engine->getScene()->forEachEntity(countEnemies);
    if (eCount < enemyCount) {
        enemyDead++;
        enemyCount = 1 + (enemyDead / 2);
    } else {
        return false;
    }
    while (eCount < enemyCount) {
        spawnRandomEntity(engine, srv);
        eCount++;
    }
    return false;
}
