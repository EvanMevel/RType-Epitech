//
// Created by evans on 01/02/2023.
//

#ifndef R_TYPE_SERVER_COOLDOWNCOMPONENT_H
#define R_TYPE_SERVER_COOLDOWNCOMPONENT_H


#include <cstddef>
#include "Engine/Component/IComponent.h"

class CooldownComponent : public IComponent {
public:
    size_t current = 0;
    size_t cooldown;
};


#endif //R_TYPE_SERVER_COOLDOWNCOMPONENT_H
