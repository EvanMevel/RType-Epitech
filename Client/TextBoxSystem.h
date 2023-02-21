//
// Created by aaama on 21/02/2023.
//

#ifndef R_TYPE_CLIENT_TEXTBOXSYSTEM_H
#define R_TYPE_CLIENT_TEXTBOXSYSTEM_H


#include "Engine/ISystem.h"
#include "Engine/Engine.h"

class TextBoxSystem : public ISystem {

public:
    void update(EnginePtr engine) override;
};


#endif //R_TYPE_CLIENT_TEXTBOXSYSTEM_H
