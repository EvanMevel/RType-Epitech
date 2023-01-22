//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H

#include "SystemHolder.h"
#include "Entity.h"
#include "EntityManager.h"

class Engine;

class Scene : public SystemHolder {
protected:
    std::vector<Entity> entities;
    EntityManager &entityManager;
public:
    Scene(EntityManager &entityManager);
    Scene(const Scene &other) : SystemHolder(other), entityManager(other.entityManager) {
        for (const auto &ent: other.entities) {
            entities.push_back(ent);
        }
    }

    ~Scene();
    void addEntity(Entity&);

    std::vector<Entity> &getEntities();
    Entity& createEntity();
    Entity& createPlayer();

    Entity &getEntityById(int id);
};

#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H
