//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_VELOCITYCOMPONENT_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_VELOCITYCOMPONENT_H


#include <cstddef>
#include "IComponent.h"

class VelocityComponent : public IComponent{
private:
    int x;
    int y;

public:
    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_VELOCITYCOMPONENT_H
