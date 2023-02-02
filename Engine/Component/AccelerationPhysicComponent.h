//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_ACCELERATIONPHYSICCOMPONENT_H
#define R_TYPE_SERVER_ACCELERATIONPHYSICCOMPONENT_H


#include "IComponent.h"
#include "Engine/Vector2i.h"

class AccelerationPhysicComponent : public IComponent {
public:
    Vector2i acceleration;
    Vector2i velocity;
    size_t maxVelocity = 0;
    size_t accelerationSlow = 1;
    size_t velocitySlow = 1;
};


#endif //R_TYPE_SERVER_ACCELERATIONPHYSICCOMPONENT_H
