//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_IPACKET_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_IPACKET_H


#include "ByteArray.h"

/**
 * @brief Interface for packets
 * @details This interface is used to define a packet that can be sent through the network
 * @see ByteArray
 */
class IPacket {
public:
    virtual void write(ByteArray &buffer) const = 0;
    virtual void read(ByteArray &buffer) = 0;
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_IPACKET_H
