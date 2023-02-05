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

#include "ProjectileCleanupSystem.h"
#include "RTypeServer.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Network/Packets/EntityDestroyPacket.h"

void ProjectileCleanupSystem::update(EnginePtr engine) {
    std::function<bool(std::shared_ptr<Entity> entity, EnginePtr engine)> f = [](std::shared_ptr<Entity> entity, EnginePtr engine) {
        auto type = entity->getComponent<EntityTypeComponent>();
        if (type == nullptr || type->getType() != EntityType::PROJECTILE) {
            return false;
        }
        auto pos = entity->getComponent<PositionComponent>();
        if (pos == nullptr) {
            return false;
        }
        if (pos->getX() < -20 || pos->getX() > 600) {
            return true;
        }
        return false;
    };

    engine->getScene()->filterEntities(f, engine);
}

ProjectileCleanupSystem::ProjectileCleanupSystem() {}
