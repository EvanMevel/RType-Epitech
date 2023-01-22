//
// Created by evans on 22/01/2023.
//

#ifndef R_TYPE_SERVER_PACKETSENDER_H
#define R_TYPE_SERVER_PACKETSENDER_H

#include "Engine/Network/Packets/PacketConsumers.h"

/**
 * @brief Describe a packet sender that can send packets to a specific socket
 * @tparam ConsumerType
 */
template<class ...ConsumerType>
class PacketSender {
protected:
    const unsigned char _magic = 232;
    PacketConsumers<ConsumerType...> packetConsumers;
public:
    bool consumeMessage(char *message, int length, ConsumerType... args) {
        unsigned char magic = *message;
        if (magic != this->_magic) {
            return false;
        }
        ByteArray arr;
        arr.write(message + 1, length - 1);
        packetConsumers.consume(arr, args...);
        return false;
    }
    PacketConsumers<ConsumerType...> &getConsumers() {
        return packetConsumers;
    }
    template<class Consumer, typename... Args>
    void addConsumer(Args&&... args) {
        packetConsumers.template addConsumer<Consumer>(std::forward<Args>(args)...);
    }
};


#endif //R_TYPE_SERVER_PACKETSENDER_H
