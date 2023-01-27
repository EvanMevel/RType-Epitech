//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_HANDSHAKEPACKET_H
#define R_TYPE_SERVER_HANDSHAKEPACKET_H


#include "IPacket.h"

class HandshakePacket : public IPacket {
public:
    static const int ID = 1;

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_HANDSHAKEPACKET_H
