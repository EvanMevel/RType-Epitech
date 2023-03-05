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

#include "LifeSystem.h"
#include "Engine/Engine.h"
#include "Client/Textures/LifeComponent.h"
#include "Client/Player/Player.h"
#include "Engine/Component/HealthComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "Textures.h"

void drawHearts(std::shared_ptr<IGraphicLib> lib, std::shared_ptr<Entity> entity, EnginePtr engine) {
    auto life = entity->getComponent<LifeComponent>();
    auto pos = entity->getComponent<PositionComponent>();

    if (life != nullptr && pos != nullptr) {
        Texture &fullHeartTexture = lib->getTextures()->getValue(Textures::HEART);
        Texture &emptyHeartTexture = lib->getTextures()->getValue(Textures::EMPTY_HEART);

        int width = fullHeartTexture->getWidth() / 4;
        auto player = engine->getModule<Player>();

        if (player == nullptr)
            return;

        auto playerLife = player->entity->getComponent<HealthComponent>();
        int ten = static_cast<int>(playerLife->getHealth()) / 10;
        int maxten = static_cast<int>((playerLife->getMaxHealth()) / 10);

        int i = 0;
        for (; i != ten; i++) {
            lib->drawTextureEx(fullHeartTexture, pos->getX() + i * width, pos->getY(), 0.0, life->getScale(), ColorCodes::COLOR_WHITE);
        }
        for (; i != maxten; i++) {
            lib->drawTextureEx(emptyHeartTexture, pos->getX() + i * width, pos->getY(), 0.0, life->getScale(), ColorCodes::COLOR_WHITE);
        }
    }
}

void LifeSystem::update(std::unique_ptr<Engine> &engine) {
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    if(engine->getScene() == nullptr)
        return;
    std::function<void(std::shared_ptr<Entity>)> draw = [&lib, &engine](std::shared_ptr<Entity> entity) {
        drawHearts(lib, entity, engine);
    };
    engine->getScene()->forEachEntity(draw);

}
