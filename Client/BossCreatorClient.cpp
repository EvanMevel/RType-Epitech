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

#include "BossCreatorClient.h"
#include "Engine/Graphic/Sprites/SpriteComponent.h"
#include "Musics.h"

void BossCreatorClient::createBoss(EnginePtr engine, std::shared_ptr<Entity> entity) {
    BossCreator::createBoss(engine, entity);
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    auto spriteComponent = entity->addComponent<SpriteComponent>();
    auto spriteProp = lib->getSpriteProperties()->getValue("BOSS");
    playMusic(engine->getModule<IGraphicLib>(),Musics::BOSS_MUSIC);
    if (spriteProp != nullptr) {
        auto sprite = spriteProp->createSprite(spriteProp);
        int spriteId = lib->getSprites()->add(sprite);
        entity->getOrCreate<SpriteComponent>()->setSpriteId(spriteId);
    }
}
