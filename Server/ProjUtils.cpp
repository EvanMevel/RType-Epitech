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

#include "ProjUtils.h"
#include "Engine/Engine.h"
#include "RTypeServer.h"
#include "Engine/Network/Packets/ProjectileHitPacket.h"
#include "Engine/Component/HealthComponent.h"
#include "Engine/Network/Packets/DamagePacket.h"
#include "Engine/Component/TeamComponent.h"
#include "Engine/Component/EntityTypeComponent2.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/PhysicComponent.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"


static void onDamage(EnginePtr engine, std::shared_ptr<Entity> cause, std::shared_ptr<Entity> victim, int damage) {
    auto entityType = victim->getComponent<EntityTypeComponent2>();

    if (entityType != nullptr && entityType->getEntityType() == "player") {
        auto server = engine->getModule<RTypeServer>();
        DamagePacket packet(victim, damage);
        server->broadcast(packet);
    }
}

CollideResult projectileHit(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other) {

    auto otherTeam = other->getComponent<TeamComponent>();
    auto selfTeam = self->getComponent<TeamComponent>();

    if (selfTeam == nullptr || otherTeam == nullptr || selfTeam->getTeam() == otherTeam->getTeam()) {
        return CollideResult::NONE;
    }
    auto server = engine->getModule<RTypeServer>();
    ProjectileHitPacket packet;
    server->broadcast(packet);

    engine->getScene()->removeEntity(self);

    auto health = other->getComponent<HealthComponent>();

    if (health != nullptr) {
        if (!health->isInvincible()) {
            health->damage(10);
            onDamage(engine, self, other, 10);
            if (!health->isAlive()) {
                engine->getScene()->removeEntity(other);
                return CollideResult::BOTH_REMOVED;
            } else {
                return CollideResult::SOURCE_REMOVED;
            }
        }
    } else {
        auto otherType = other->getComponent<EntityTypeComponent2>();
        if (otherType != nullptr && otherType->getEntityType() == "projectile") {
            engine->getScene()->removeEntity(other);
            return CollideResult::BOTH_REMOVED;
        }
    }
    return CollideResult::NONE;
}

void shoot(EnginePtr engine, std::shared_ptr<Entity> source, int xMult) {
    auto pos = source->getComponent<PositionComponent>();
    auto team = source->getComponent<TeamComponent>();

    auto projectile = engine->getScene()->unsafeCreateEntity(engine, "projectile", pos->x, pos->y + 20);

    projectile->getComponent<PhysicComponent>()->velocity.x = 10 * xMult;

    projectile->addComponent<ColliderComponent>(projectileHit);

    projectile->addComponent<TeamComponent>(team->getTeam());

    EntityInfoPacket newEntityPacket(projectile);
    engine->getModule<RTypeServer>()->broadcast(newEntityPacket);
}
