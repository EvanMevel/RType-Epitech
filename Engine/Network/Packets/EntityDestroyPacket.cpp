//
// Created by evans on 31/01/2023.
//

#include "EntityDestroyPacket.h"

EntityDestroyPacket::EntityDestroyPacket(size_t entityId) : entityId(entityId) {}

EntityDestroyPacket::EntityDestroyPacket() {}

void EntityDestroyPacket::write(ByteArray &buffer) const {
    buffer << entityId;
}

void EntityDestroyPacket::read(ByteArray &buffer) {
    buffer >> entityId;
}
