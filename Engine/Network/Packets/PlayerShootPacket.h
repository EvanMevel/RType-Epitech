//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERSHOOTPACKET_H
#define R_TYPE_SERVER_PLAYERSHOOTPACKET_H


#include "IPacket.h"

class PlayerShootPacket : public IPacket {
public:
    static const int ID = 8;

    size_t playerId;

    explicit PlayerShootPacket(size_t playerId);

    PlayerShootPacket();

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_PLAYERSHOOTPACKET_H
