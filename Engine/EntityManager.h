//
// Created by evans on 20/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYMANAGER_H
#define R_TYPE_SERVER_ENTITYMANAGER_H


#include <cstddef>
#include "Entity.h"

/**
 * @brief The EntityManager class is used to keep track of entity ids
 */
class EntityManager {
private:
    std::size_t nextId;

public:
    EntityManager();
    Entity createEntity();
};


#endif //R_TYPE_SERVER_ENTITYMANAGER_H
