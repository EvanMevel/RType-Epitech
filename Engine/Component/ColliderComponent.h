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

#ifndef R_TYPE_SERVER_COLLIDERCOMPONENT_H
#define R_TYPE_SERVER_COLLIDERCOMPONENT_H

#include "Engine/Component/IComponent.h"
#include "Engine/EngineTypes.h"
#include <functional>

/**
 * @brief Describes the result of a collision
 */
enum CollideResult {
    NONE = 0,
    SOURCE_REMOVED = 1,
    TARGET_REMOVED = 2,
    BOTH_REMOVED = 3
};

using CollideFunction = std::function<CollideResult(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other)>;

/**
 * @brief A component that describes a collider
 * @details A collider is a component that can collide with other entities
 */
class ColliderComponent : public IComponent {
private:
    CollideFunction _onCollision;

public:
    ColliderComponent();

    explicit ColliderComponent(const CollideFunction &onCollision);

    CollideResult onCollision(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other) const;

    [[maybe_unused]] void setOnCollision(const CollideFunction &onCollision);
};


#endif //R_TYPE_SERVER_COLLIDERCOMPONENT_H
