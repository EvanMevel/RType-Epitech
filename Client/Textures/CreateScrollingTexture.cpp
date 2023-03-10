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

#include "CreateScrollingTexture.h"

std::shared_ptr<Entity> createScrollingTextureComponent(const std::shared_ptr<IGraphicLib> &lib, const std::shared_ptr<Scene> &sc,
                                                        Textures texture, int speed) {
    auto scrollingEntity = sc->createEntity();

    scrollingEntity->addComponent<PositionComponent>(0, 0);

    const Texture &scrollingTexture = lib->getTextures()->getValue(texture);

    auto scrollingComponent = scrollingEntity->addComponent<ScrollingTextureComponent>();
    scrollingComponent->setTextureId(texture);
    scrollingComponent->setScrollingSpeed(speed);
    scrollingComponent->setWidth(scrollingTexture->getWidth());
    auto scale = (float)lib->getWindow().getHeight() / (float)scrollingTexture->getHeight();
    scrollingComponent->setScale(scale);
    return scrollingEntity;
}
