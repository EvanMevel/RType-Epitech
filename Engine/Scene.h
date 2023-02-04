//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H

#include <functional>
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
    std::mutex entityMutex;
public:
    Scene(EntityManager &entityManager);

    Scene(const Scene &other) : SystemHolder(other), entityManager(other.entityManager) {
        for (const auto &ent: other.entities) {
            entities.push_back(ent);
        }
    }

    ~Scene();

    std::vector<std::shared_ptr<Entity>> &getEntities();

    void forEachEntity(std::function<void(std::shared_ptr<Entity>)> func);
    void forEachEntity(std::function<void(std::shared_ptr<Entity>, EnginePtr engine)> func, EnginePtr engine);
    void filterEntities(std::function<bool(std::shared_ptr<Entity>)> filter);
    void filterEntities(std::function<bool(std::shared_ptr<Entity>, EnginePtr engine)> func, EnginePtr engine);

    void addEntity(std::shared_ptr<Entity>);
    std::shared_ptr<Entity> createEntity();
    std::shared_ptr<Entity> unsafeCreateEntity();
    std::shared_ptr<Entity> getEntityById(size_t id);

    void removeEntity(std::shared_ptr<Entity> entity);
    void removeEntity(size_t entityId);

    std::unique_ptr<std::lock_guard<std::mutex>> obtainLock();

};

#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H
