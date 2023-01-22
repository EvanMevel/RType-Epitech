//
// Created by aaama on 17/01/2023.
//

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
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITY_H
