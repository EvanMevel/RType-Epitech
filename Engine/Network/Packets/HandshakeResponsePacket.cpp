//
// Created by evans on 24/01/2023.
//

#include "HandshakeResponsePacket.h"

HandshakeResponsePacket::HandshakeResponsePacket(HandshakeResponsePacketType type, unsigned long long int currentTick)
        : type(type), currentTick(currentTick) {}

HandshakeResponsePacket::HandshakeResponsePacket() {}

HandshakeResponsePacketType HandshakeResponsePacket::getType() const {
    return type;
}

unsigned long long int HandshakeResponsePacket::getCurrentTick() const {
    return currentTick;
}

void HandshakeResponsePacket::write(ByteArray &buffer) const {
    buffer << type << currentTick;
}

void HandshakeResponsePacket::read(ByteArray &buffer) {
    int ptype;
    buffer >> ptype;
    this->type = static_cast<HandshakeResponsePacketType>(ptype);
    buffer >> currentTick;
}
