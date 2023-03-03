//
// Created by aaama on 02/03/2023.
//

#ifndef R_TYPE_CLIENT_TEXTSYSTEM_H
#define R_TYPE_CLIENT_TEXTSYSTEM_H


#include "Engine/ISystem.h"
#include "Engine/Engine.h"

class TextSystem : public ISystem {
public:
    void update(EnginePtr engine) override;

};


#endif //R_TYPE_CLIENT_TEXTSYSTEM_H
