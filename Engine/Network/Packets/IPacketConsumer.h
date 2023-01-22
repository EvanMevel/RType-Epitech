//
// Created by evans on 21/01/2023.
//

#ifndef R_TYPE_SERVER_IPACKETCONSUMER_H
#define R_TYPE_SERVER_IPACKETCONSUMER_H


#include "ByteArray.h"

/**
 * Interface for packet Consumer
 * @tparam Args Types of the arguments
 */
template<class... Args>
class IPacketConsumer {
public:
    virtual void consumePacket(ByteArray &buffer, Args ...args) = 0;
    virtual int getId() = 0;
};


#endif //R_TYPE_SERVER_IPACKETCONSUMER_H
