//
// Created by evans on 31/01/2023.
//

#include "EntityInfoPacket.h"

void EntityInfoPacket::write(ByteArray &buffer) const {
    buffer << id << type << x << y;
}

void EntityInfoPacket::read(ByteArray &buffer) {
    buffer >> id;
    int ptype;
    buffer >> ptype;
    this->type = static_cast<EntityType>(ptype);
    buffer >> x >> y;
}

EntityInfoPacket::EntityInfoPacket(size_t id, EntityType type, int x, int y) : id(id), type(type), x(x), y(y) {}

EntityInfoPacket::EntityInfoPacket() {}

EntityInfoPacket::EntityInfoPacket(std::shared_ptr<Entity> entity) :
    EntityInfoPacket(entity, entity->getComponent<EntityTypeComponent>(), entity->getComponent<PositionComponent>()) {
}

EntityInfoPacket::EntityInfoPacket(std::shared_ptr<Entity> entity, std::shared_ptr<EntityTypeComponent> type,
                                   std::shared_ptr<PositionComponent> pos) {
    this->id = entity->getId();
    if (type) {
        this->type = type->getType();
    }
    if (pos) {
        this->x = pos->getX();
        this->y = pos->getY();
    }
}

EntityInfoPacket::EntityInfoPacket(std::shared_ptr<Entity> entity, EntityType type,
                                   std::shared_ptr<PositionComponent> pos) {
    this->id = entity->getId();
    this->type = type;
    if (pos) {
        this->x = pos->getX();
        this->y = pos->getY();
    }
}
