// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "PlayerInfoPacket.h"
#include "Server/PlayerInfoComponent.h"

PlayerInfoPacket::PlayerInfoPacket() : playerId(0), x(0), y(0), playerNumber(0) {
}

PlayerInfoPacket::PlayerInfoPacket(EntityPtr entity) {
    playerId = entity->getId();
    auto pos = entity->getComponent<PositionComponent>();
    if (pos) {
        x = pos->getX();
        y = pos->getY();
    } else {
        throw std::runtime_error("Player has no position component");
    }
    auto player = entity->getComponent<PlayerInfoComponent>();
    if (player) {
        playerNumber = (int) player->playerNumber;
    } else {
        throw std::runtime_error("Player has no player info component");
    }
}

void PlayerInfoPacket::write(ByteArray &buffer) const {
    buffer << playerId << x << y << playerNumber;
}

void PlayerInfoPacket::read(ByteArray &buffer) {
    buffer >> playerId >> x >> y >> playerNumber;
}
