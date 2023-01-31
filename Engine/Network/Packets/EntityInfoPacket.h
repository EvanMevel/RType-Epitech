//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYINFOPACKET_H
#define R_TYPE_SERVER_ENTITYINFOPACKET_H


#include "IPacket.h"
#include "Engine/EntityType.h"

class EntityInfoPacket : public IPacket {
public:
    static const int ID = 7;
    size_t id;
    EntityType type;
    int x;
    int y;

    EntityInfoPacket();

    EntityInfoPacket(size_t id, EntityType type, int x, int y);

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_ENTITYINFOPACKET_H
