//
// Created by gugue on 24/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYVELOCITYACCELERATIONPOSITIONPACKET_H
#define R_TYPE_SERVER_ENTITYVELOCITYACCELERATIONPOSITIONPACKET_H

#include "IPacket.h"

/**
 * @brief EntityVelocityAccelerationPositionPacket is a packet used to send position, acceleration and velocity of the Entity
 */
class EntityVelocityAccelerationPositionPacket : public IPacket {
public:
    int entityId;
    Vector2i pos;
    Vector2i velocity;
    Vector2i acceleration;
public:
    static const int ID = 2;

    EntityVelocityAccelerationPositionPacket() {}

    EntityVelocityAccelerationPositionPacket(int entityId, Vector2i pos, Vector2i velocity, Vector2i acceleration) : entityId(entityId), pos(pos), velocity(velocity), acceleration(acceleration) {}

    void write(ByteArray &buffer) const override {
        buffer << entityId << pos << velocity << acceleration;
    }

    void read(ByteArray &buffer) override {
        buffer >> entityId >> pos >> velocity >> acceleration;
    }
};

#endif //R_TYPE_SERVER_ENTITYVELOCITYACCELERATIONPOSITIONPACKET_H

