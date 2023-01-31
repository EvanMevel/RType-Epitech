//
// Created by gugue on 24/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYVELOCITYPACKET_H
#define R_TYPE_SERVER_ENTITYVELOCITYPACKET_H

#include "IPacket.h"

/**
 * @brief EntityVelocityPacket is a packet used to send position, acceleration and velocity of the Entity
 */
class EntityVelocityPacket : public IPacket {
public:
    size_t entityId;
    Vector2i pos;
    Vector2i velocity;
    Vector2i acceleration;
    unsigned long long tick;
public:
    static const int ID = 2;

    EntityVelocityPacket();

    EntityVelocityPacket(size_t entityId, const Vector2i &pos, const Vector2i &velocity, const Vector2i &acceleration,
                         unsigned long long int tick);

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};

#endif //R_TYPE_SERVER_ENTITYVELOCITYPACKET_H

