//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H

#include "SystemHolder.h"
#include "Entity.h"
#include "EntityManager.h"

class Engine;

/**
 * @brief Scene class is the base class for all scenes
 * @details it is a system and entity holder
 */
class Scene : public SystemHolder {
protected:
    std::vector<std::shared_ptr<Entity>> entities;
    EntityManager &entityManager;
public:
    Scene(EntityManager &entityManager);
    Scene(const Scene &other) : SystemHolder(other), entityManager(other.entityManager) {
        for (const auto &ent: other.entities) {
            entities.push_back(ent);
        }
    }

    ~Scene();
    void addEntity(std::shared_ptr<Entity>);

    std::vector<std::shared_ptr<Entity>> &getEntities();
    std::shared_ptr<Entity> createEntity();
    std::shared_ptr<Entity> createPlayer();

    std::shared_ptr<Entity> getEntityById(int id);
};

#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H
