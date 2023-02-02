//
// Created by evans on 02/02/2023.
//

#include <functional>
#include "ColliderComponent.h"

void ColliderComponent::onCollision(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other,
                                    std::unordered_map<size_t, std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>>>> &teams) {
    if (_onCollision != nullptr)
        _onCollision(engine, self, other, teams);
}
