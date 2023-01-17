//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ICONSUMER_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ICONSUMER_H

class Engine;
template<typename Type>

class IConsumer {
    virtual void consume(Engine,Type) = 0;
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ICONSUMER_H
