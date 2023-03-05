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

#include "CollectableComponent.h"
#include "Engine.h"
#include "EntityTypeComponent.h"
#include "engineLua/LuaWeaponFactory.h"
#include "WeaponComponent.h"
#include "CollectableModule.h"

CollideResult onCollisionCollectableComponent(EnginePtr engine, std::shared_ptr<Entity> self,
                                              std::shared_ptr<Entity> other) {
    auto type = other->getComponent<EntityTypeComponent>();
    if (type == nullptr || type->getEntityType() != "player") {
        return CollideResult::NONE;
    }
    auto collectable = self->getComponent<CollectableComponent>();
    if (collectable == nullptr) {
        return CollideResult::NONE;
    }
    auto collectModule = engine->getModule<CollectableModule>();
    if (collectModule == nullptr) {
        return CollideResult::NONE;
    }
    if (!collectModule->collect(engine, other, collectable)) {
        return CollideResult::NONE;
    }

    engine->getScene()->removeEntity(self);
    return CollideResult::SOURCE_REMOVED;
}

CollectableComponent::CollectableComponent(const std::string &type, const std::string &value) : type(type),
                                                                                                value(value) {}

const std::string &CollectableComponent::getType() const {
    return type;
}

const std::string &CollectableComponent::getValue() const {
    return value;
}
