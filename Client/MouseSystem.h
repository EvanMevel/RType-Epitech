//
// Created by aaama on 02/02/2023.
//

#ifndef R_TYPE_SERVER_MOUSESYSTEM_H
#define R_TYPE_SERVER_MOUSESYSTEM_H


#include "Engine/ISystem.h"

class MouseSystem : public ISystem {
public:
    void update(EnginePtr engine) override;
};


#endif //R_TYPE_SERVER_MOUSESYSTEM_H
