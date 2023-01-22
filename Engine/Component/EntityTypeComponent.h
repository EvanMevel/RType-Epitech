//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITYTYPECOMPONENT_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITYTYPECOMPONENT_H


#include <cstddef>
#include "IComponent.h"
#include "../EntityType.h"

class EntityTypeComponent : public IComponent {
private:
    EntityType type;
public:
    explicit EntityTypeComponent() = default;

    EntityType getType() const;

    void setType(EntityType type);
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITYTYPECOMPONENT_H
