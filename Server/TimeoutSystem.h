//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_TIMEOUTSYSTEM_H
#define R_TYPE_SERVER_TIMEOUTSYSTEM_H

#define RTYPE_TIMEOUT 5000

#include "Engine/ISystem.h"

class TimeoutSystem : public ISystem {
public:
    TimeoutSystem();

    void update(EnginePtr engine) override;

    std::string getName() override;
};


#endif //R_TYPE_SERVER_TIMEOUTSYSTEM_H
