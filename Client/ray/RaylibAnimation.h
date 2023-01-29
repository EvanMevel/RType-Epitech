//
// Created by audre on 29/01/2023.
//

#ifndef R_TYPE_SERVER_RAYLIBANIMATION_H
#define R_TYPE_SERVER_RAYLIBANIMATION_H


#include <string>
#include "Engine/Graphic/IAnimation.h"
namespace ray {
#include "raylib.h"
}

class RaylibAnimation : public IAnimation{
public:
    RaylibAnimation(const std::string &texturePath);

    void setAnimationFrame(int frame) override;
};


#endif //R_TYPE_SERVER_RAYLIBANIMATION_H
