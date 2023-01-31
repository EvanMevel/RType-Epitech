//
// Created by evans on 31/01/2023.
//

#include "EntityInfoConsumer.h"
#include "Engine/Component/PositionComponent.h"
#include "Client/FixTextureComponent.h"

EntityInfoConsumer::EntityInfoConsumer(const std::unordered_map<EntityType, std::shared_ptr<ITexture>> &textures)
        : textures(textures) {

}

void EntityInfoConsumer::consume(EntityInfoPacket &packet, Engine &e) {
    auto entity = e.getScene()->getEntityById(packet.id);
    auto pos = entity->getOrCreate<PositionComponent>();
    pos->setX(packet.x);
    pos->setY(packet.y);
    auto texture = entity->getOrCreate<FixTextureComponent>();
    texture->setTexture(textures[packet.type]);
}