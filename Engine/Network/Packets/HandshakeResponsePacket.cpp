//
// Created by evans on 24/01/2023.
//

#include "HandshakeResponsePacket.h"

HandshakeResponsePacket::HandshakeResponsePacket(HandshakeResponsePacketType type, unsigned long long int currentTick,
                                                 unsigned long long int startedTime) : type(type),
                                                                                       currentTick(currentTick),
                                                                                       startedTime(startedTime) {}

HandshakeResponsePacket::HandshakeResponsePacket() {}

HandshakeResponsePacketType HandshakeResponsePacket::getType() const {
    return type;
}

unsigned long long int HandshakeResponsePacket::getCurrentTick() const {
    return currentTick;
}

unsigned long long int HandshakeResponsePacket::getStartedTime() const {
    return startedTime;
}

void HandshakeResponsePacket::write(ByteArray &buffer) const {
    buffer << type << currentTick << startedTime;
}

void HandshakeResponsePacket::read(ByteArray &buffer) {
    int ptype;
    buffer >> ptype;
    this->type = static_cast<HandshakeResponsePacketType>(ptype);
    buffer >> currentTick >> startedTime;
}
