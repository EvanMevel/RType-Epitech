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

#include "EntityVelocityPacket.h"


EntityVelocityPacket::EntityVelocityPacket(size_t entityId, const Vector2i &pos, const Vector2i &velocity,
                                           const Vector2i &acceleration, unsigned long long int tick) : entityId(
        entityId), pos(pos), velocity(velocity), acceleration(acceleration), tick(tick) {}

EntityVelocityPacket::EntityVelocityPacket() {
}

void EntityVelocityPacket::write(ByteArray &buffer) const {
    buffer << entityId << pos << velocity << acceleration << tick;
}

void EntityVelocityPacket::read(ByteArray &buffer) {
    buffer >> entityId >> pos >> velocity >> acceleration >> tick;
}

EntityVelocityPacket::EntityVelocityPacket(std::shared_ptr<Entity> entity, unsigned long long int tick) {
    this->entityId = entity->getId();
    auto posComponent = entity->getComponent<PositionComponent>();
    if (posComponent) {
        this->pos = posComponent->clone();
    }
    auto physicsComponent = entity->getComponent<PhysicComponent>();
    if (physicsComponent) {
        this->velocity = physicsComponent->velocity.clone();
        this->acceleration = physicsComponent->acceleration.clone();
    }
    this->tick = tick;
}

