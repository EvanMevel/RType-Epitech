//
// Created by evans on 21/01/2023.
//

#ifndef R_TYPE_SERVER_PACKETCONSUMER_H
#define R_TYPE_SERVER_PACKETCONSUMER_H

#include "../../IConsumer.h"
#include "ByteArray.h"
#include "IPacketConsumer.h"

/**
 * @brief PacketConsumer is a consumer that will consume a ByteArray and will call the callback with the packe
 * @tparam Packet The packet that will be consumed
 * @tparam Args The arguments that will be passed to the callback
 */
template<class Packet, class... Args>
class PacketConsumer : public IPacketConsumer<Args...> {
public:
    void consumePacket(ByteArray &buffer, Args ...args) override {
        Packet packet;
        packet.read(buffer);
        this->consume(packet, args...);
    }
    int getId() override {
        return Packet::ID;
    }
    /**
     * @brief The callback that will be called when the packet is consumed
     * @param packet The packet that was consumed
     * @param args The arguments that were passed to the consumePacket method
     */
    virtual void consume(Packet &packet, Args ...args) = 0;
};


#endif //R_TYPE_SERVER_PACKETCONSUMER_H
