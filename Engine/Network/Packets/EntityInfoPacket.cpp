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
