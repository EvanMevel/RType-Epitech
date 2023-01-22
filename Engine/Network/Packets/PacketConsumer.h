//
// Created by evans on 21/01/2023.
//

#ifndef R_TYPE_SERVER_PACKETCONSUMER_H
#define R_TYPE_SERVER_PACKETCONSUMER_H

#include "../../IConsumer.h"
#include "ByteArray.h"
#include "IPacketConsumer.h"

template<class Packet>
class PacketConsumer : public IPacketConsumer{
public:
    void consumePacket(ByteArray &buffer) override {
        Packet packet;
        packet.read(buffer);
        this->consume(packet);
    }
    int getId() override {
        return Packet::ID;
    }
    virtual void consume(Packet &packet) = 0;
};


#endif //R_TYPE_SERVER_PACKETCONSUMER_H
