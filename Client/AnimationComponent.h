//
// Created by audre on 29/01/2023.
//

#ifndef R_TYPE_SERVER_ANIMATIONCOMPONENT_H
#define R_TYPE_SERVER_ANIMATIONCOMPONENT_H


#include <memory>
#include "Engine/Component/IComponent.h"
#include "Engine/Graphic/IAnimation.h"

class AnimationComponent : public IComponent {
private:
    std::shared_ptr<IAnimation> animation;
public:
    int frameDelay = 6;
    int currentFrame = 0;
    int currentAnimFrame = 0;

    AnimationComponent();

    ~AnimationComponent() override;

    const std::shared_ptr<IAnimation> &getAnimation() const;

    void setAnimation(const std::shared_ptr<IAnimation> &animation);
};


#endif //R_TYPE_SERVER_ANIMATIONCOMPONENT_H
