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

#include "AnimationSystem.h"
#include "Engine/Engine.h"
#include "AnimationComponent.h"
#include "Engine/Component/PositionComponent.h"
/**
 * @brief update current animation frame if we have to change it(depends on frmaedelay) we change it and then update
 */
void AnimationSystem::update(EnginePtr engine) {
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    if(engine->getScene() == nullptr)
        return;
    auto lock = engine->getScene()->obtainLock();
    for (auto &entity: engine->getScene()->getEntities()) {
        auto animationComponent = entity->getComponent<AnimationComponent>();
        auto posComponent = entity->getComponent<PositionComponent>();
        if (animationComponent != nullptr && posComponent != nullptr) {
           animationComponent->currentFrame = (animationComponent->currentFrame + 1) % animationComponent->frameDelay;
           if (animationComponent->currentFrame == 0){
               animationComponent->currentAnimFrame = (animationComponent->currentAnimFrame + 1) % animationComponent->getAnimation()->frame;
               animationComponent->getAnimation()->setAnimationFrame(animationComponent->currentAnimFrame);
           }
           lib->drawAnimation(animationComponent->getAnimation(),posComponent->getX(),posComponent->getY(), ColorCodes::COLOR_WHITE);
        }
    }
}
