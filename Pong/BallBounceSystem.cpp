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

#include "BallBounceSystem.h"
#include "Engine/Engine.h"
#include "Engine/Hitbox.h"
#include "Engine/Component/PhysicComponent.h"
#include "Sounds.h"

void BallBounceSystem::update(std::unique_ptr<Engine> &engine) {
    if (!ball || !player1 || !player2) {
        return;
    }
    auto physic = ball->getComponent<PhysicComponent>();
    Hitbox ballHitBox(ball);
    Hitbox player1HitBox(player1);
    Hitbox player2HitBox(player2);

    if (ballHitBox.isColliding(player1HitBox)) {
        if (physic->velocity.x < 0) {
            auto lib = engine->getModule<IGraphicLib>();
            lib->execOnLibThread(playSound, lib, Sounds::BABEGI);
            physic->velocity.x = -physic->velocity.x;
        }
    } else if (ballHitBox.isColliding(player2HitBox)) {
        if (physic->velocity.x > 0) {
            auto lib = engine->getModule<IGraphicLib>();
            lib->execOnLibThread(playSound, lib, Sounds::FORTINITE);
            physic->velocity.x = -physic->velocity.x;
        }
    }
}

BallBounceSystem::BallBounceSystem(const std::shared_ptr<Entity> &ball, const std::shared_ptr<Entity> &player1,
                                   const std::shared_ptr<Entity> &player2) : ball(ball), player1(player1),
                                                                             player2(player2) {}
