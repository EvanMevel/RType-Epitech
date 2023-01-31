//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_HANDSHAKERESPONSEPACKET_H
#define R_TYPE_SERVER_HANDSHAKERESPONSEPACKET_H

#include "IPacket.h"

enum HandshakeResponsePacketType {
    OK = 0,
    KO = 1,
    FULL = 2
};

class HandshakeResponsePacket : public IPacket{
private:
    HandshakeResponsePacketType type;
    unsigned long long currentTick;
public:
    static const int ID = 3;

    HandshakeResponsePacket(HandshakeResponsePacketType type, unsigned long long int currentTick);

    unsigned long long int getCurrentTick() const;

    HandshakeResponsePacket();

    HandshakeResponsePacketType getType() const;

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_HANDSHAKERESPONSEPACKET_H
