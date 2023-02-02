//
// Created by audre on 29/01/2023.
//

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
