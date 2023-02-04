//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Scene.h"
#include "Engine.h"
#include "EntityTypeComponent.h"
#include "TimeUtil.h"

Scene::~Scene() {
}

void Scene::addEntity(std::shared_ptr<Entity> entity) {
    std::lock_guard<std::mutex> lock(entityMutex);
    this->entities.push_back(entity);
}

std::vector<std::shared_ptr<Entity>> &Scene::getEntities() {
    return this->entities;
}

std::shared_ptr<Entity> Scene::createEntity() {
    std::lock_guard<std::mutex> lock(entityMutex);
    this->entities.push_back(entityManager.createEntity());
    return this->entities.back();
}

std::shared_ptr<Entity> Scene::unsafeCreateEntity() {
    this->entities.push_back(entityManager.createEntity());
    return this->entities.back();
}

Scene::Scene(EntityManager &entityManager) : entityManager(entityManager) {

}

std::shared_ptr<Entity> Scene::getEntityById(size_t id) {
    for (auto &ent: entities) {
        if (ent->getId() == id) {
            return ent;
        }
    }
    std::shared_ptr<Entity> ent = std::make_shared<Entity>(id);
    entities.push_back(ent);
    return entities.back();
}

void Scene::removeEntity(std::shared_ptr<Entity> entity) {
    std::lock_guard<std::mutex> lock(entityMutex);
    for (auto it = entities.begin(); it != entities.end(); it++) {
        if (*it == entity) {
            entities.erase(it);
            return;
        }
    }
}

void Scene::removeEntity(size_t entityId) {
    std::lock_guard<std::mutex> lock(entityMutex);
    for (auto it = entities.begin(); it != entities.end(); it++) {
        if (it->get()->getId() == entityId) {
            entities.erase(it);
            return;
        }
    }
}

std::unique_ptr<std::lock_guard<std::mutex>> Scene::obtainLock() {
    return std::make_unique<std::lock_guard<std::mutex>>(entityMutex);
}

void Scene::forEachEntity(std::function<void(std::shared_ptr<Entity>)> func) {
    std::lock_guard<std::mutex> lock(entityMutex);
    for (auto &ent: entities) {
        if (ent == nullptr)
            continue;
        func(ent);
    }
}

void Scene::forEachEntity(std::function<void(std::shared_ptr<Entity>, EnginePtr)> func, std::unique_ptr<Engine> &engine) {
    std::lock_guard<std::mutex> lock(entityMutex);
    for (auto &ent: entities) {
        if (ent == nullptr)
            continue;
        func(ent, engine);
    }
}

void Scene::filterEntities(std::function<bool(std::shared_ptr<Entity>)> filter) {
    std::lock_guard<std::mutex> lock(entityMutex);
    entities.erase(
            std::remove_if(entities.begin(), entities.end(), [&](std::shared_ptr<Entity> &entity) {
                if (entity == nullptr)
                    return false;
                return filter(entity);
            }),
            entities.end()
    );
}

void Scene::filterEntities(std::function<bool(std::shared_ptr<Entity>, EnginePtr)> filter, std::unique_ptr<Engine> &engine) {
    std::lock_guard<std::mutex> lock(entityMutex);
    entities.erase(
            std::remove_if(entities.begin(), entities.end(), [&](std::shared_ptr<Entity> &entity) {
                if (entity == nullptr)
                    return false;
                return filter(entity, engine);
            }),
            entities.end()
            );
}
