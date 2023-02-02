//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_TEAMCOMPONENT_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_TEAMCOMPONENT_H


#include <cstddef>
#include "IComponent.h"

class TeamComponent : public IComponent{
    size_t team;
public:
    void setTeam(size_t team);

public:
    size_t getTeam() const;
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_TEAMCOMPONENT_H
