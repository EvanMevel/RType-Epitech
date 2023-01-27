//
// Created by evans on 27/01/2023.
//

#include <iostream>
#include "PlayerInfoConsumer.h"

void PlayerInfoConsumer::consume(PlayerInfoPacket &packet, Engine &e) {
    std::cout << "We are player " << packet.playerId << " at " << packet.x << " " << packet.y << std::endl;
}
