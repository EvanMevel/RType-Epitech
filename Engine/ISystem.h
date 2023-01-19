//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ISYSTEM_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ISYSTEM_H

class Engine;

class ISystem {
public:
    ISystem();
    ~ISystem();

    virtual void update(Engine&);
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ISYSTEM_H
