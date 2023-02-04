//
// Created by evans on 01/02/2023.
//

#include "EntityVelocityPacketConsumer.h"
#include "Engine/TickUtil.h"

void EntityVelocityPacketConsumer::consume(EntityVelocityPacket &packet, EnginePtr engine,
                                           RTypeServer server) {
    auto ticker = engine->getModule<TickUtil>();

    //std::cout << "ServerTick: " << packet.tick << " Client tick: " << ticker->getCurrentTick() << std::endl;

    auto entity = engine->getScene()->getEntityById(packet.entityId);
    auto pos = entity->getOrCreate<PositionComponent>();
    auto physics = entity->getOrCreate<AccelerationPhysicComponent>();

    pos->setX(packet.pos.x);
    pos->setY(packet.pos.y);

    physics->velocity = packet.velocity;
    physics->acceleration = packet.acceleration;
}