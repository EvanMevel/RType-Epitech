//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITY_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITY_H


#include <unordered_map>
#include <typeindex>
#include <any>
#include <cstddef>
#include "Component/IComponent.h"

// We have to implement addComponent, getComponent and hasComponent in the header file because they are templates functions
class Entity {
private:
    std::unordered_map<std::type_index, IComponent*> components;
    size_t id;
public:
    Entity();
    explicit Entity(size_t id);

    size_t getId() const;

    template<class Type>
    Type *addComponent() {
        Type *component = new Type();
        components[std::type_index(typeid(Type))] = component;
        return component;
    }

    template <typename T>
    T* getComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

    template<class Type>
    bool hasComponent() const {
        return components.find(std::type_index(typeid(Type))) != components.end();
    }
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITY_H
