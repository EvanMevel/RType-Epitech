//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_PACKETSERIALIZER_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_PACKETSERIALIZER_H


template<class Packet>

class PacketSerializer {
    virtual void* serialize(Packet) = 0;
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_PACKETSERIALIZER_H
