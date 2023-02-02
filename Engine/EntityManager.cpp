//
// Created by evans on 20/01/2023.
//

#include "EntityManager.h"

EntityManager::EntityManager() : nextId(0) {

}

std::shared_ptr<Entity> EntityManager::createEntity() {
    return std::make_shared<Entity>(nextId++);
}

EntityManager::EntityManager(size_t nextId) : nextId(nextId) {}
