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

#include "SynchronizedWeapon.h"
#include "RTypeServer.h"
#include "Engine/Network/Packets/ProjectileHitPacket.h"
#include "Engine/Component/EntityTypeComponent2.h"
#include "Engine/Network/Packets/DamagePacket.h"
#include "Engine/TickUtil.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"


SynchronizedWeapon::SynchronizedWeapon(const std::string &projectile, size_t cooldown, int velX, int velY) : Weapon(
        projectile, cooldown, velX, velY) {

}

std::shared_ptr<Entity> SynchronizedWeapon::shootAtPos(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> shooter, int x, int y) {
    auto projectile = Weapon::shootAtPos(engine, shooter, x, y);

    auto ticker = engine->getModule<TickUtil>();

    EntityVelocityPacket packet(projectile, ticker->getCurrentTick());
    engine->getModule<RTypeServer>()->broadcast(packet);
    return projectile;
}

void SynchronizedWeapon::shoot(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> shooter) {
    Weapon::shoot(engine, shooter);
}

CollideResult SynchronizedWeapon::projectileHit(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> self,
                                                std::shared_ptr<Entity> other) {
    CollideResult res = Weapon::projectileHit(engine, self, other);
    if (res == CollideResult::NONE) {
        return res;
    }

    auto server = engine->getModule<RTypeServer>();
    ProjectileHitPacket packet;
    server->broadcast(packet);

    return res;
}

void SynchronizedWeapon::onDamage(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> cause,
                                  std::shared_ptr<Entity> victim, int damage) {
    auto entityType = victim->getComponent<EntityTypeComponent2>();

    if (entityType != nullptr && entityType->getEntityType() == "player") {
        auto server = engine->getModule<RTypeServer>();
        DamagePacket packet(victim, damage);
        server->broadcast(packet);
    }
}
