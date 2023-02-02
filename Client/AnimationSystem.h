//
// Created by audre on 29/01/2023.
//

#ifndef R_TYPE_SERVER_ANIMATIONSYSTEM_H
#define R_TYPE_SERVER_ANIMATIONSYSTEM_H


#include "Engine/ISystem.h"

class AnimationSystem : public ISystem {
public:
    void update(EnginePtr engine) override;

};


#endif //R_TYPE_SERVER_ANIMATIONSYSTEM_H
