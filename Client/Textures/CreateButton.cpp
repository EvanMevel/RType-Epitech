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

#include "CreateButton.h"
#include "Engine/Component/HitboxComponent.h"
#include "Client/HitboxFixComponent.h"

std::shared_ptr<Entity> createButton(const std::shared_ptr<IGraphicLib> &lib, std::shared_ptr<Scene> sc, Textures texture, int x, int y)
{
    auto button = sc->createEntity();

    button->addComponent<EntityTypeComponent>()->setType(EntityType::BUTTON);
    button->addComponent<FixTextureComponent>()->setTextureId(texture);

    auto pos = button->addComponent<PositionComponent>();
    pos->setX(x);
    pos->setY(y);

    const Texture& buttonTexture = lib->getTextures()->getValue(texture);
    auto hitboxPlaybutton = button->addComponent<HitboxComponent>();
    hitboxPlaybutton->setLengthX(buttonTexture->getWidth());
    hitboxPlaybutton->setLengthY(buttonTexture->getHeight());

    auto hitboxFixComponent = button->addComponent<HitboxFixComponent>();

    hitboxFixComponent->setHitbox(Hitbox(pos,hitboxPlaybutton));

    return button;
}
