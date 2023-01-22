//
// Created by evans on 22/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYTESTPACKET_H
#define R_TYPE_SERVER_ENTITYTESTPACKET_H

#include "IPacket.h"

class EntityTestPacket : public IPacket {
public:
    int entityId;
    int x;
    int y;
public:
    static const int ID = 4;

    EntityTestPacket() {}

    EntityTestPacket(int entityId, int x, int y) : entityId(entityId), x(x), y(y) {}

    void write(ByteArray &buffer) const override {
        buffer << entityId << x << y;
    }

    void read(ByteArray &buffer) override {
        buffer >> entityId >> x >> y;
    }
};

#endif //R_TYPE_SERVER_ENTITYTESTPACKET_H
