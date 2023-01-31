//
// Created by evans on 31/01/2023.
//

#include "EntityDestroyConsumer.h"

void EntityDestroyConsumer::consume(EntityDestroyPacket &packet, Engine &e) {
    e.getScene()->removeEntity(packet.entityId);
}
