//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERMOVEPACKET_H
#define R_TYPE_SERVER_PLAYERMOVEPACKET_H

#include "IPacket.h"

class PlayerMovePacket : public IPacket {
public:
    static const int ID = 6;

    size_t playerId;
    Vector2i acceleration;

    PlayerMovePacket(size_t playerId, const Vector2i &acceleration);

    PlayerMovePacket();

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_PLAYERMOVEPACKET_H
