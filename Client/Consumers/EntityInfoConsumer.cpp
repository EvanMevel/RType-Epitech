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

#include "EntityInfoConsumer.h"
#include "Engine/EntityUtils.h"
#include "Client/FixTextureComponent.h"
#include "Client/SpriteComponent.h"
#include "Client/SpriteManager.h"

void EntityInfoConsumer::consume(EntityInfoPacket &packet, EnginePtr engine, RTypeServer server) {
    auto entity = engine->getScene()->getEntityById(packet.id);
    auto spriteManager = engine->getModule<SpriteManager>();
    std::shared_ptr<Sprite> sprite;
    if (packet.type == EntityType::PROJECTILE) {
        entity::initProjectile(entity, packet.x, packet.y, 0);
        if (packet.entityInfo == 0) {
            sprite = spriteManager->getSprite(SpriteType::PROJECTILE_1);
        } else {
            sprite = spriteManager->getSprite(SpriteType::PROJECTILE_2);
        }
    } else if (packet.type == EntityType::ENEMY) {
        entity::initEnemy(entity, packet.x, packet.y);
        sprite = spriteManager->getSprite(SpriteType::ENEMY);
    } else if (packet.type == EntityType::PLAYER) {
        entity::initPlayer(entity, packet.x, packet.y);
        SpriteType type = static_cast<SpriteType>(((int) SpriteType::PLAYER_1) + packet.entityInfo - 1);
        sprite = spriteManager->getSprite(type);
    }
    if (sprite) {
        auto spriteComponent = entity->getOrCreate<SpriteComponent>();
        spriteComponent->setSprite(sprite);
    }
}
