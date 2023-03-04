//
// Created by gugue on 04/03/2023.
//

#ifndef PONG_PLAYGAMESYSTEM_H
#define PONG_PLAYGAMESYSTEM_H


#include "Engine/Engine.h"

class PlayGameSystem: public ISystem {
public:
    void update(EnginePtr engine) override;
};


#endif //PONG_PLAYGAMESYSTEM_H
