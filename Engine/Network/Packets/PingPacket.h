//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_PINGPACKET_H
#define R_TYPE_SERVER_PINGPACKET_H


#include "IPacket.h"

class PingPacket : public IPacket {
public:
    static const int ID = 0;

    static PingPacket current();

    long long timestamp = 0;
    PingPacket();

    explicit PingPacket(long long int timestamp);

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_PINGPACKET_H
