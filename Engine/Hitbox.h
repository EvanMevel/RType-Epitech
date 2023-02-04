//
// Created by evans on 02/02/2023.
//

#ifndef R_TYPE_SERVER_HITBOX_H
#define R_TYPE_SERVER_HITBOX_H

#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/HitboxComponent.h"
#include "Engine/Entity.h"

class Hitbox {
public:
    int x;
    int y;
    size_t width;
    size_t height;

    Hitbox(int x, int y, size_t width, size_t height);

    Hitbox(std::shared_ptr<PositionComponent> pos, std::shared_ptr<HitboxComponent> hitbox);

    Hitbox(std::shared_ptr<Entity> entity);

    bool isColliding(Hitbox &other);

    bool contains(int x, int y);

};


#endif //R_TYPE_SERVER_HITBOX_H
