//
// Created by evans on 27/01/2023.
//

#include "PlayerInfoPacket.h"

void PlayerInfoPacket::write(ByteArray &buffer) const {
    buffer << playerId << x << y;
}

void PlayerInfoPacket::read(ByteArray &buffer) {
    buffer >> playerId >> x >> y;
}
