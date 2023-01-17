//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_PACKETDESERIALIZER_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_PACKETDESERIALIZER_H

template<class Packet>

class PacketDeserializer {
    virtual Packet deserializer(void*) = 0;
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_PACKETDESERIALIZER_H
