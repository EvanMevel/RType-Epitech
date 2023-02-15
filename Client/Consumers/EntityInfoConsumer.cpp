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
#include "Client/Textures/FixTextureComponent.h"
#include "Client/Sprites/SpriteComponent.h"
#include "Client/Sounds.h"

void EntityInfoConsumer::consume(EntityInfoPacket &packet, EnginePtr engine, RTypeServer server) {
    auto entity = engine->getScene()->getOrCreateEntityById(packet.id);
    auto lib = engine->getModule<IGraphicLib>();
    std::shared_ptr<SpriteProperty> spriteProp = nullptr;
    if (packet.type == EntityType::PROJECTILE) {
        entity::initProjectile(entity, packet.x, packet.y, 0);
        if (packet.entityInfo == 0) {
            spriteProp = lib->getSpriteProperties()->getValue("projectile1");
            lib->execOnLibThread(playSound, lib, Sounds::PROJECTILE_SHOOT);
        } else {
            spriteProp = lib->getSpriteProperties()->getValue("projectile2");
        }
    } else if (packet.type == EntityType::ENEMY) {
        entity::initEnemy(entity, packet.x, packet.y);
        std::string spriteName = "enemy" + std::to_string(packet.entityInfo + 1);
        spriteProp = lib->getSpriteProperties()->getValue(spriteName);
    } else if (packet.type == EntityType::PLAYER) {
        entity::initPlayer(entity, packet.x, packet.y);
        std::string spriteName = "player" + std::to_string(packet.entityInfo + 1);
        spriteProp = lib->getSpriteProperties()->getValue(spriteName);
    }
    if (spriteProp != nullptr) {
        auto sprite = spriteProp->createSprite(spriteProp);
        int spriteId = lib->getSprites()->add(sprite);
        entity->getOrCreate<SpriteComponent>()->setSpriteId(spriteId);
    }
}
