//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYDESTROYPACKET_H
#define R_TYPE_SERVER_ENTITYDESTROYPACKET_H


#include "IPacket.h"

class EntityDestroyPacket : public IPacket {
public:
    static const int ID = 9;
    size_t entityId;

    EntityDestroyPacket();

    explicit EntityDestroyPacket(size_t entityId);

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_ENTITYDESTROYPACKET_H
