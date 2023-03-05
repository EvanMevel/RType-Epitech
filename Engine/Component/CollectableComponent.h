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

#ifndef PONG_COLLECTABLECOMPONENT_H
#define PONG_COLLECTABLECOMPONENT_H


#include "IComponent.h"
#include "ColliderComponent.h"

/**
 * @brief Component that defines the collectable of an entity
 */
class CollectableComponent : public IComponent {
private:
    std::string type;
    std::string value;

public:
    CollectableComponent(const std::string &type, const std::string &value);

    const std::string &getType() const;

    const std::string &getValue() const;

};

CollideResult onCollisionCollectableComponent(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other);


#endif //PONG_COLLECTABLECOMPONENT_H