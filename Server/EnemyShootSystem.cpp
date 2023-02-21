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

#include "EnemyShootSystem.h"
#include "Engine/Engine.h"
#include "Engine/EntityUtils.h"
#include "Engine/Component/CooldownComponent.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"
#include "RTypeServer.h"
#include "Engine/Network/Packets/ProjectileHitPacket.h"
#include "Engine/Component/IAComponent.h"
#include "Engine/Component/ColliderComponent.h"
#include "Engine/Component/TeamComponent.h"
#include "Engine/engineLua/LuaEntityTypeFactory.h"
#include "Engine/Component/PhysicComponent.h"


static void projectileHit(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other,
                   std::unordered_map<size_t, std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>>>> &teams,
                          std::function<void(EnginePtr engine, std::shared_ptr<Entity> touched, int damages)> onDamage) {
    auto server = engine->getModule<RTypeServer>();

    ProjectileHitPacket packet;
    server->broadcast(packet);

    entity::projectileHit(engine, self, other, teams, onDamage);
}

void EnemyShootSystem::update(std::unique_ptr<Engine> &engine) {
    auto lock = engine->getScene()->obtainLock();
    auto &entities = engine->getScene()->getEntities();
    for (size_t i = 0; i < entities.size(); i++) {
        auto &ent = entities[i];
        auto ia = ent->getComponent<IAComponent>();
        if (ia) {
            auto cd = ent->getComponent<CooldownComponent>();
            auto pos = ent->getComponent<PositionComponent>();
            if (cd == nullptr || pos == nullptr) {
                continue;
            }
            cd->current++;
            if (cd->current >= cd->cooldown) {
                cd->current = 0;
                auto typeFactory = engine->getModule<LuaEntityTypeFactory>();
                auto projectile = engine->getScene()->unsafeCreateEntity();
                typeFactory->initEntity(projectile, "projectile");
                projectile->addComponent<PositionComponent>(pos->x, pos->y + 20);
                projectile->getComponent<PhysicComponent>()->velocity.x = -10;

                projectile->addComponent<ColliderComponent>(projectileHit);

                projectile->addComponent<TeamComponent>(1);

                EntityInfoPacket newEntityPacket(projectile);
                engine->getModule<RTypeServer>()->broadcast(newEntityPacket);
            }
        }
    }
}
