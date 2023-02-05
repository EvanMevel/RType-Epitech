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

#include "ScrollingTextureSystem.h"
#include "Engine/Graphic/IGraphicLib.h"
#include "Engine/Engine.h"
#include "Engine/Component/PositionComponent.h"
#include "ScrollingTextureComponent.h"

void drawScrollingTexture(std::shared_ptr<IGraphicLib> lib, std::shared_ptr<Entity> entity) {
    auto scrollingComponent = entity->getComponent<ScrollingTextureComponent>();
    auto posComponent = entity->getComponent<PositionComponent>();
    if (scrollingComponent != nullptr && posComponent != nullptr) {
        scrollingComponent->applySpeed();
        auto texture =  scrollingComponent->getTexture();
        lib->drawTextureEx(texture, posComponent->getX() + scrollingComponent->getScroll(), posComponent->getY(),0.0,scrollingComponent->getScale(), ColorCodes::COLOR_WHITE);
        lib->drawTextureEx(texture, posComponent->getX() + texture->getWidth() + scrollingComponent->getScroll(), posComponent->getY(),0.0,scrollingComponent->getScale(), ColorCodes::COLOR_WHITE);
    }
}

void ScrollingTextureSystem::update(std::unique_ptr<Engine> &engine) {
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    if(engine->getScene() == nullptr)
        return;
    std::function<void(std::shared_ptr<Entity>)> draw = [&lib](std::shared_ptr<Entity> entity) {
        drawScrollingTexture(lib, entity);
    };
    engine->getScene()->forEachEntity(draw);
}
