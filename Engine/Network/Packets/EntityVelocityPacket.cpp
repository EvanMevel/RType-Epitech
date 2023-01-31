//
// Created by evans on 29/01/2023.
//

#include "EntityVelocityPacket.h"


EntityVelocityPacket::EntityVelocityPacket(size_t entityId, const Vector2i &pos, const Vector2i &velocity,
                                           const Vector2i &acceleration, unsigned long long int tick) : entityId(
        entityId), pos(pos), velocity(velocity), acceleration(acceleration), tick(tick) {}

EntityVelocityPacket::EntityVelocityPacket() {
}

void EntityVelocityPacket::write(ByteArray &buffer) const {
    buffer << entityId << pos << velocity << acceleration << tick;
}

void EntityVelocityPacket::read(ByteArray &buffer) {
    buffer >> entityId >> pos >> velocity >> acceleration >> tick;
}

