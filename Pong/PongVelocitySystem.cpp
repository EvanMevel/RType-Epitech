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

#include "PongVelocitySystem.h"
#include "PlayerComponent.h"
#include "Pong.h"
#include "BallComponent.h"
#include "Engine/Engine.h"
#include "Sounds.h"

void PongVelocitySystem::applyVelocity(EnginePtr engine, std::shared_ptr<Entity> entity,
                                       std::shared_ptr<PositionComponent> pos,
                                       std::shared_ptr<PhysicComponent> physic,
                                       std::vector<std::pair<std::shared_ptr<Entity>, Hitbox>> inanimates) {
    VelocitySystem::applyVelocity(engine, entity, pos, physic);

    if (entity->hasComponent<PlayerComponent>()) {
        if (pos->y < 0) {
            pos->y = 0;
        } else if (pos->y > PONG_WINDOW_HEIGHT - PONG_PLAYER_HEIGHT) {
            pos->y = PONG_WINDOW_HEIGHT - PONG_PLAYER_HEIGHT;
        }
    } else if (entity->hasComponent<BallComponent>()) {
        if (pos->y < 0) {
            pos->y = 0;
            physic->velocity.y = -physic->velocity.y;
            auto lib = engine->getModule<IGraphicLib>();
            lib->execOnLibThread(playSound, lib, Sounds::THUD);
        } else if (pos->y > PONG_WINDOW_HEIGHT - PONG_BALL_HEIGHT) {
            pos->y = PONG_WINDOW_HEIGHT - PONG_BALL_HEIGHT;
            physic->velocity.y = -physic->velocity.y;
            auto lib = engine->getModule<IGraphicLib>();
            lib->execOnLibThread(playSound, lib, Sounds::THUD);
        }
    }

}
