//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_HITBOXCOMPONENT_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_HITBOXCOMPONENT_H


#include <cstddef>
#include "IComponent.h"

class HitboxComponent : public IComponent{
    size_t length_x;
public:
    void setLengthX(size_t lengthX);

private:
    size_t length_y;
public:
    void setLengthY(size_t lengthY);

public:
    size_t getLengthX() const;

    size_t getLengthY() const;
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_HITBOXCOMPONENT_H
