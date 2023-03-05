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
#include "Engine/Engine.h"
#include "PlayerMoveSystem.h"
#include "PlayerComponent.h"
#include "Engine/Graphic/Textures/FixTextureComponent.h"
#include "Pong.h"
#include "Engine/Component/HitboxComponent.h"
#include "PongVelocitySystem.h"
#include "BallComponent.h"
#include "BallBounceSystem.h"
#include "WinConditionSystem.h"
#include "Textures.h"

std::shared_ptr<Scene> gameScene(EnginePtr engine){
    auto sc = engine->createScene<Scene>();
    auto lib = engine->getModule<IGraphicLib>();

    sc->addSystem<PongVelocitySystem>();
    sc->addSystem<PlayerMoveSystem>();

    int y = PONG_WINDOW_HEIGHT / 2 - PONG_PLAYER_HEIGHT / 2;

    auto player1 = sc->createEntity();
    player1->addComponent<PositionComponent>(PONG_GOALS_WIDTH, y);
    auto physic = player1->addComponent<PhysicComponent>();
    physic->maxVelocity = 8;
    player1->addComponent<PlayerComponent>()->number = 1;
    player1->addComponent<FixTextureComponent>()->setTextureId(Textures::PLAYER);
    player1->addComponent<HitboxComponent>(PONG_PLAYER_WIDTH, PONG_PLAYER_HEIGHT);

    auto player2 = sc->createEntity();
    player2->addComponent<PositionComponent>(PONG_WINDOW_WIDTH - PONG_GOALS_WIDTH - PONG_PLAYER_WIDTH, y);
    physic = player2->addComponent<PhysicComponent>();
    physic->maxVelocity = 8;
    player2->addComponent<PlayerComponent>()->number = 2;
    player2->addComponent<FixTextureComponent>()->setTextureId(Textures::PLAYER);
    player2->addComponent<HitboxComponent>(PONG_PLAYER_WIDTH, PONG_PLAYER_HEIGHT);

    auto ball = sc->createEntity();
    ball->addComponent<PositionComponent>(PONG_WINDOW_WIDTH / 2 - PONG_BALL_WIDTH / 2, PONG_WINDOW_HEIGHT / 2 - PONG_BALL_HEIGHT / 2);
    physic = ball->addComponent<PhysicComponent>();
    physic->velocitySlow = 0;
    ball->addComponent<BallComponent>();
    ball->addComponent<FixTextureComponent>()->setTextureId(Textures::BALL);
    ball->addComponent<HitboxComponent>(PONG_BALL_WIDTH, PONG_BALL_HEIGHT);

    sc->addSystem<BallBounceSystem>(ball, player1, player2);
    sc->addSystem<WinConditionSystem>(ball);

    return sc;
}
