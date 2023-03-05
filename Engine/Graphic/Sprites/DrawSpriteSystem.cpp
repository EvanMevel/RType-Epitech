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

#include "DrawSpriteSystem.h"
#include "Engine/Engine.h"
#include "Engine/Component/PositionComponent.h"

void drawEntitySprite(std::shared_ptr<IGraphicLib> lib, std::shared_ptr<Entity> entity) {
    auto spriteComponent = entity->getComponent<SpriteComponent>();
    auto positionComponent = entity->getComponent<PositionComponent>();
    if (spriteComponent && positionComponent) {
        int spriteId = spriteComponent->getSpriteId();
        auto sprite = lib->getSprites()->get(spriteId);
        if (sprite == nullptr)
            return;
        sprite->updateRect();
        lib->drawSprite(sprite, positionComponent->getX(), positionComponent->getY(), ColorCodes::COLOR_WHITE);
    }
}

void DrawSpriteSystem::update(std::unique_ptr<Engine> &engine) {
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    if(engine->getScene() == nullptr)
        return;
    std::function<void(std::shared_ptr<Entity>)> draw = [&lib](std::shared_ptr<Entity> entity) {
        drawEntitySprite(lib, entity);
    };
    engine->getScene()->forEachEntity(draw);
}