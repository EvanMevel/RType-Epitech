//
// Created by evans on 28/01/2023.
//

#include "PlayerMovePacket.h"

PlayerMovePacket::PlayerMovePacket() {}

PlayerMovePacket::PlayerMovePacket(int playerId, const Vector2i &acceleration) : playerId(playerId),
                                                                                 acceleration(acceleration) {}

void PlayerMovePacket::write(ByteArray &buffer) const {
    buffer << playerId << acceleration.x << acceleration.y;
}

void PlayerMovePacket::read(ByteArray &buffer) {
    buffer >> playerId >> acceleration.x >> acceleration.y;
}
