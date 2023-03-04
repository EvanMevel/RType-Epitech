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
#include "Engine/engineLua/LuaEntityTypeFactory.h"
#include "Client/Textures/TextureNameComponent.h"
#include "Client/BossCreator.h"

void EntityInfoConsumer::consume(EntityInfoPacket &packet, EnginePtr engine, RTypeServer server) {
    auto entity = engine->getScene()->getOrCreateEntityById(packet.id);
    entity->addComponent<PositionComponent>(packet.x, packet.y);

    auto lib = engine->getModule<IGraphicLib>();
    std::shared_ptr<SpriteProperty> spriteProp = nullptr;

    auto typeFactory = engine->getModule<LuaEntityTypeFactory>();
    typeFactory->initEntity(entity, packet.type);

    if (packet.type.find("projectile") != std::string::npos) {
        spriteProp = lib->getSpriteProperties()->getValue(packet.type);
    } else if (packet.type == "player") {
        std::string spriteName = "player" + std::to_string(packet.entityInfo + 1);
        spriteProp = lib->getSpriteProperties()->getValue(spriteName);
    } else if (packet.type.find("enemy") != std::string::npos) {
        spriteProp = lib->getSpriteProperties()->getValue(packet.type);
    }else if(packet.type == "BOSS"){
        engine->getModule<BossCreator>()->createBoss(engine, entity);
    }
    if (spriteProp != nullptr) {
        auto sprite = spriteProp->createSprite(spriteProp);
        int spriteId = lib->getSprites()->add(sprite);
        entity->getOrCreate<SpriteComponent>()->setSpriteId(spriteId);
    } else {
        auto texture = lib->getTexturesReg()->getValue(packet.type);
        if (texture != nullptr) {
            entity->getOrCreate<TextureNameComponent>(packet.type);
        }
    }
}
