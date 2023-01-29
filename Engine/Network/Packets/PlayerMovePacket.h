//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERMOVEPACKET_H
#define R_TYPE_SERVER_PLAYERMOVEPACKET_H

#include "IPacket.h"

class PlayerMovePacket : public IPacket {
public:
    static const int ID = 6;

    int playerId;
    Vector2i acceleration;

    PlayerMovePacket(int playerId, const Vector2i &acceleration);

    PlayerMovePacket();

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_PLAYERMOVEPACKET_H
