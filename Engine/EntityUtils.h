//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYUTILS_H
#define R_TYPE_SERVER_ENTITYUTILS_H

#include "Engine/Entity.h"
#include "Engine/EntityType.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/AccelerationPhysicComponent.h"
#include "Engine/Component/HitboxComponent.h"
#include "Engine/Component/TeamComponent.h"
#include "Engine/Component/ColliderComponent.h"

namespace entity {
    void initPlayer(std::shared_ptr<Entity> entity, int x, int y);

    void initProjectile(std::shared_ptr<Entity> entity, int x, int y, int velX);

    void initEnemy(std::shared_ptr<Entity> entity, int x, int y);
}


#endif //R_TYPE_SERVER_ENTITYUTILS_H
