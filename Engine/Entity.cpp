//
// Created by aaama on 17/01/2023.
//

#include "Entity.h"

Entity::Entity() {}

Entity::Entity(size_t id) : id(id) {}

size_t Entity::getId() const {
    return id;
}


