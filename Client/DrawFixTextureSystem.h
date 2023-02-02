//
// Created by evans on 20/01/2023.
//

#ifndef R_TYPE_SERVER_DRAWFIXTEXTURESYSTEM_H
#define R_TYPE_SERVER_DRAWFIXTEXTURESYSTEM_H

#include "Engine/ISystem.h"

class DrawFixTextureSystem : public ISystem {
public:
    void update(EnginePtr engine) override;

    std::string getName() override;

};


#endif //R_TYPE_SERVER_DRAWFIXTEXTURESYSTEM_H
