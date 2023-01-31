//
// Created by evans on 31/01/2023.
//

#include "EntityInfoPacket.h"

void EntityInfoPacket::write(ByteArray &buffer) const {
    buffer << id << type << x << y;
}

void EntityInfoPacket::read(ByteArray &buffer) {
    buffer >> id;
    int ptype;
    buffer >> ptype;
    this->type = static_cast<EntityType>(ptype);
    buffer >> x >> y;
}

EntityInfoPacket::EntityInfoPacket(size_t id, EntityType type, int x, int y) : id(id), type(type), x(x), y(y) {}

EntityInfoPacket::EntityInfoPacket() {}
