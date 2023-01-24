//
// Created by evans on 24/01/2023.
//

#include "HandshakeResponsePacket.h"

HandshakeResponsePacket::HandshakeResponsePacket(HandshakeResponsePacketType type) : type(type) {}

HandshakeResponsePacket::HandshakeResponsePacket() {}

HandshakeResponsePacketType HandshakeResponsePacket::getType() const {
    return type;
}

void HandshakeResponsePacket::write(ByteArray &buffer) const {
    buffer << type;
}

void HandshakeResponsePacket::read(ByteArray &buffer) {
    int ptype;
    buffer >> ptype;
    this->type = static_cast<HandshakeResponsePacketType>(ptype);
}
