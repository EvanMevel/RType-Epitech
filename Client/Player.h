//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYER_H
#define R_TYPE_SERVER_PLAYER_H

#include "Engine/Entity.h"

class Player {
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;
    std::shared_ptr<Entity> entity;
};


#endif //R_TYPE_SERVER_PLAYER_H
