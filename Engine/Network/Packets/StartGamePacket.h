//
// Created by gugue on 04/03/2023.
//

#ifndef PONG_STARTGAMEPACKET_H
#define PONG_STARTGAMEPACKET_H


#include "IPacket.h"

class StartGamePacket : public IPacket {
public:
    static const int ID = 18;

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};
#endif //PONG_STARTGAMEPACKET_H
