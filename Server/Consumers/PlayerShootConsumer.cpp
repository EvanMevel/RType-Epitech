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

#include "PlayerShootConsumer.h"
#include "Engine/EntityUtils.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"
#include "Engine/Network/Packets/ProjectileHitPacket.h"

PlayerShootConsumer::PlayerShootConsumer(EnginePtr e) : RTypePlayerPacketConsumer(e) {}

static void projectileHit(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other,
                   std::unordered_map<size_t, std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>>>> &teams,
                  std::function<void(EnginePtr engine, std::shared_ptr<Entity> touched, int damages)> onDamage) {
    auto server = engine->getModule<RTypeServer>();

    ProjectileHitPacket packet;
    server->broadcast(packet);

    entity::projectileHit(engine, self, other, teams, onDamage);
}

void PlayerShootConsumer::consume(PlayerShootPacket &packet, std::shared_ptr<NetClient> client,
                                  std::shared_ptr<ClientData> data, std::shared_ptr<Entity> player) {
    if (player == nullptr)
        return;

    auto pos = player->getComponent<PositionComponent>();
    if (pos == nullptr)
        return;
    auto projectile = e->getScene()->createEntity();
    entity::initProjectile(projectile, pos->x + 20, pos->y + 20, 10);

    projectile->addComponent<ColliderComponent>(projectileHit);

    projectile->addComponent<TeamComponent>(0);

    EntityInfoPacket newEntityPacket(projectile);
    e->getModule<RTypeServer>()->broadcast(newEntityPacket);
}
