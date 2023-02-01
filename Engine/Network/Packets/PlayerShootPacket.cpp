//
// Created by evans on 31/01/2023.
//

#include "PlayerShootPacket.h"

PlayerShootPacket::PlayerShootPacket(size_t playerId) : playerId(playerId) {}

PlayerShootPacket::PlayerShootPacket() {}

void PlayerShootPacket::write(ByteArray &buffer) const {
    buffer << playerId;
}

void PlayerShootPacket::read(ByteArray &buffer) {
    buffer >> playerId;
}
