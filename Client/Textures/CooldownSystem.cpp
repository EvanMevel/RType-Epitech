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

//
// Created by gugue on 15/02/2023.
//

#include "CooldownSystem.h"
#include "CooldownComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "Client/Player/Player.h"

void drawCooldown(std::shared_ptr<IGraphicLib> lib, std::shared_ptr<Entity> entity, EnginePtr engine) {
    auto cooldown = entity->getComponent<CooldownComponent2>();
    auto pos = entity->getComponent<PositionComponent>();

    if (cooldown != nullptr && pos != nullptr) {
        Texture &canShootTexture = lib->getTextures()->getValue(Textures::CAN_SHOOT);
        Texture &cantShootTexture = lib->getTextures()->getValue(Textures::CANT_SHOOT);

        auto player = engine->getModule<Player>();

        if (player == nullptr)
            return;
        if (player->cooldown > 0)
            lib->drawTexture(cantShootTexture, pos->getX() - canShootTexture->getWidth(), pos->getY(), ColorCodes::COLOR_WHITE);
        else
            lib->drawTexture(canShootTexture, pos->getX() - canShootTexture->getWidth(), pos->getY(), ColorCodes::COLOR_WHITE);
    }
}

void CooldownSystem::update(std::unique_ptr<Engine> &engine) {
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    if(engine->getScene() == nullptr)
        return;
    std::function<void(std::shared_ptr<Entity>)> draw = [&lib, &engine](std::shared_ptr<Entity> entity) {
        drawCooldown(lib, entity, engine);
    };
    engine->getScene()->forEachEntity(draw);

}