//
// Created by evans on 20/01/2023.
//

#include "EntityManager.h"

EntityManager::EntityManager() : nextId(0) {

}

Entity EntityManager::createEntity() {
    return Entity(nextId++);
}
