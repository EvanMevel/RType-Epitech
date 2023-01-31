//
// Created by evans on 27/01/2023.
//

#include "PlayerInfoPacket.h"

PlayerInfoPacket::PlayerInfoPacket() {

}

void PlayerInfoPacket::write(ByteArray &buffer) const {
    buffer << playerId << x << y;
}

void PlayerInfoPacket::read(ByteArray &buffer) {
    buffer >> playerId >> x >> y;
}

PlayerInfoPacket::PlayerInfoPacket(std::shared_ptr<Entity> entity, std::shared_ptr<PositionComponent> pos) {
    playerId = entity->getId();
    if (pos) {
        x = pos->getX();
        y = pos->getY();
    }
}

PlayerInfoPacket::PlayerInfoPacket(std::shared_ptr<Entity> entity) : PlayerInfoPacket(entity, entity->getComponent<PositionComponent>()) {

}
