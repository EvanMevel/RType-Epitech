//
// Created by evans on 31/01/2023.
//

#include "EntityInfoConsumer.h"
#include "Engine/EntityUtils.h"
#include "Client/FixTextureComponent.h"

EntityInfoConsumer::EntityInfoConsumer(const std::unordered_map<EntityType, std::shared_ptr<ITexture>> &textures)
        : textures(textures) {

}

void EntityInfoConsumer::consume(EntityInfoPacket &packet, EnginePtr engine, RTypeServer server) {
    auto entity = engine->getScene()->getEntityById(packet.id);
    if (packet.type == EntityType::PROJECTILE) {
        entity::initProjectile(entity, packet.x, packet.y, 0);
    } else if (packet.type == EntityType::ENEMY) {
        entity::initEnemy(entity, packet.x, packet.y);
    } else if (packet.type == EntityType::PLAYER) {
        entity::initPlayer(entity, packet.x, packet.y);
    }
    auto texture = entity->getOrCreate<FixTextureComponent>();
    texture->setTexture(textures[packet.type]);
}
