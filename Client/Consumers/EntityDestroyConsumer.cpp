//
// Created by evans on 31/01/2023.
//

#include "EntityDestroyConsumer.h"

void EntityDestroyConsumer::consume(EntityDestroyPacket &packet, EnginePtr engine, RTypeServer server) {
    engine->getScene()->removeEntity(packet.entityId);
}
