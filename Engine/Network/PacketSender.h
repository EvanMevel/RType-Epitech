//
// Created by evans on 22/01/2023.
//

#ifndef R_TYPE_SERVER_PACKETSENDER_H
#define R_TYPE_SERVER_PACKETSENDER_H

#include "Engine/Network/Packets/PacketConsumers.h"

class PacketSender {
protected:
    const unsigned char _magic = 242;
    PacketConsumers packetConsumers;
public:
    bool consumeMessage(char *message, int length) {
        unsigned char magic = *message;
        if (magic != this->_magic) {
            return false;
        }
        ByteArray arr;
        arr.write(message + 1, length - 1);
        packetConsumers.consume(arr);
        return false;
    }
    /*template<class Consumer, typename... Args>
    void addConsumer(Args&&... args) {
        packetConsumers.addConsumer<Consumer>(std::forward<Args>(args)...);
    }*/
};


#endif //R_TYPE_SERVER_PACKETSENDER_H
