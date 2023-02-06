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
#include "Engine/EntityUtils.h"
#include "Server/PlayerInfoComponent.h"
#include "Server/EnemyInfoComponent.h"

EntityInfoPacket::EntityInfoPacket() : id(0), type(EntityType::ENEMY), x(0), y(0) {}

EntityInfoPacket::EntityInfoPacket(EntityPtr entity) :
    EntityInfoPacket(entity, entity->getComponent<EntityTypeComponent>(), entity->getComponent<PositionComponent>()) {
}

EntityInfoPacket::EntityInfoPacket(EntityPtr entity, std::shared_ptr<EntityTypeComponent> type,
                                   std::shared_ptr<PositionComponent> pos) {
    this->id = entity->getId();
    if (type) {
        this->type = type->getType();
        if (type->getType() == EntityType::PROJECTILE) {
            auto team = entity->getComponent<TeamComponent>();
            if (team) {
                this->entityInfo = (int) team->getTeam();
            }
        } else if (type->getType() == EntityType::PLAYER) {
            auto playerInfo = entity->getComponent<PlayerInfoComponent>();
            if (playerInfo) {
                this->entityInfo = (int) playerInfo->playerNumber;
            }
        } else if (type->getType() == EntityType::ENEMY) {
            auto enemyInfo = entity->getComponent<EnemyInfoComponent>();
            if (enemyInfo) {
                this->entityInfo = (int) enemyInfo->type;
            }
        }
    }
    if (pos) {
        this->x = pos->getX();
        this->y = pos->getY();
    }
}

void EntityInfoPacket::write(ByteArray &buffer) const {
    buffer << id << type << x << y << entityInfo;
}

void EntityInfoPacket::read(ByteArray &buffer) {
    buffer >> id;
    int ptype;
    buffer >> ptype;
    this->type = static_cast<EntityType>(ptype);
    buffer >> x >> y >> entityInfo;
}
