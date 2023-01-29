//
// Created by audre on 29/01/2023.
//

#include "AnimationComponent.h"

AnimationComponent::AnimationComponent() {

}

AnimationComponent::~AnimationComponent() {

}

const std::shared_ptr<IAnimation> &AnimationComponent::getAnimation() const {
    return animation;
}

void AnimationComponent::setAnimation(const std::shared_ptr<IAnimation> &animation) {
    AnimationComponent::animation = animation;
}
