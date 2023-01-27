//
// Created by evans on 27/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERINFOPACKET_H
#define R_TYPE_SERVER_PLAYERINFOPACKET_H


#include "IPacket.h"

class PlayerInfoPacket : public IPacket {

public:
    static const int ID = 5;
    PlayerInfoPacket() = default;

    size_t playerId;
    int x;
    int y;

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_PLAYERINFOPACKET_H
