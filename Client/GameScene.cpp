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

#include "GameScene.h"
#include "SceneEnum.h"
#include "Engine/SceneHolder.h"
#include "Engine/VelocitySystem.h"
#include "Client/Consumers/PlayerInfoConsumer.h"
#include "ScrollingTextureComponent.h"

std::shared_ptr<Entity> createScrollinTextureComponent(std::shared_ptr<IGraphicLib> lib, std::shared_ptr<Scene> sc, const std::string &texturePath, int speed) {
    auto scrollingEntity = sc->createEntity();
    auto scrollingComponent = scrollingEntity->addComponent<ScrollingTextureComponent>();
    auto pos = scrollingEntity->addComponent<PositionComponent>();
    pos->setX(0);
    pos->setY(0);
    auto scrollingTexture =  lib->createTexture(texturePath);
    scrollingComponent->setTexture(scrollingTexture);
    scrollingComponent->setScrollingSpeed(speed);
    auto scale = (float)lib->getWindow().getHeight() / (float)scrollingTexture->getHeight();
    scrollingComponent->setScale(scale);
    return scrollingEntity;
}

std::shared_ptr<Scene> gameScene(EnginePtr engine){
    auto sc = engine->createScene<Scene>();
    auto lib = engine->getModule<IGraphicLib>();

    auto background = createScrollinTextureComponent(lib, sc, "../Client/assets/Starry background  - Layer 01 - Solid colour.png",-1);
    auto fourthground = createScrollinTextureComponent(lib, sc, "../Client/assets/Starry background  - Layer 02 - Shadows.png",-2);
    auto thirdground = createScrollinTextureComponent(lib, sc, "../Client/assets/Starry background  - Layer 02 - Shadows 2.png",-2);
    auto secondground = createScrollinTextureComponent(lib, sc, "../Client/assets/Starry background  - Layer 03 - Stars.png",-3);
    auto firstground = createScrollinTextureComponent(lib, sc, "../Client/assets/Starry background  - Layer 03 - Stars 2.png",-4);

    return sc;
}