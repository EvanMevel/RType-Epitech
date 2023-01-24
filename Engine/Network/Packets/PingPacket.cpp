//
// Created by evans on 24/01/2023.
//

#include "PingPacket.h"
#include "Engine/TimeUtil.h"

PingPacket::PingPacket() {}

PingPacket::PingPacket(long long int timestamp) : timestamp(timestamp) {}

void PingPacket::write(ByteArray &buffer) const {
    buffer << timestamp;
}

void PingPacket::read(ByteArray &buffer) {
    buffer >> timestamp;
}

PingPacket PingPacket::current() {
    return PingPacket(getCurrentTime());
}
