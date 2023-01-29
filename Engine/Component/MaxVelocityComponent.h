//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_MAXVELOCITYCOMPONENT_H
#define R_TYPE_SERVER_MAXVELOCITYCOMPONENT_H


#include <cstdio>
#include "IComponent.h"

class MaxVelocityComponent : public IComponent {
private:
    std::size_t maxVelocity;
public:
    explicit MaxVelocityComponent(size_t maxVelocity);

    MaxVelocityComponent();

    size_t getMaxVelocity() const;

    void setMaxVelocity(size_t maxVelocity);
};


#endif //R_TYPE_SERVER_MAXVELOCITYCOMPONENT_H
