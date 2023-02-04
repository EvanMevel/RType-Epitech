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

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITY_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITY_H

#include <memory>
#include <unordered_map>
#include <typeindex>
#include <any>
#include <cstddef>
#include "Component/IComponent.h"

/**
 * @brief Entity is the base class for all entities of the ECS
 * @details an entity is a container for components
 */
class Entity {
private:
    std::unordered_map<std::type_index, std::shared_ptr<IComponent>> components;
    size_t id;
public:
    Entity();
    explicit Entity(size_t id);

    virtual ~Entity();

    size_t getId() const;

    template<class Type, class ...Args>
    std::shared_ptr<Type> addComponent(Args ...args) {
        auto alreadyExist = components.find(typeid(Type));
        if (alreadyExist != components.end()) {
            return std::dynamic_pointer_cast<Type> (alreadyExist->second);
        }
        std::shared_ptr<IComponent> component = std::make_shared<Type>(args...);
        components[std::type_index(typeid(Type))] = component;
        return std::dynamic_pointer_cast<Type> (component);
    }

    template <typename Type>
    std::shared_ptr<Type> getComponent() {
        auto it = components.find(std::type_index(typeid(Type)));
        if (it != components.end()) {
            return std::dynamic_pointer_cast<Type> (it->second);
        }
        return nullptr;
    }

    template<class Type>
    bool hasComponent() const {
        return components.find(std::type_index(typeid(Type))) != components.end();
    }

    template<class Type, class ...Args>
    std::shared_ptr<Type> getOrCreate(Args ...args) {
        auto component = getComponent<Type>();
        if (component == nullptr)
            return addComponent<Type>();
        return component;
    }
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITY_H
