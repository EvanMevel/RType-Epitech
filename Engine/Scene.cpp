//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Scene.h"
#include "Engine.h"
#include "EntityTypeComponent.h"

Scene::~Scene() {
}

void Scene::addEntity(std::shared_ptr<Entity> entity) {
    this->entities.push_back(entity);
}

std::vector<std::shared_ptr<Entity>> &Scene::getEntities() {
    return this->entities;
}

std::shared_ptr<Entity> Scene::createEntity() {
    this->entities.push_back(entityManager.createEntity());
    return this->entities.back();
}

std::shared_ptr<Entity> Scene::createPlayer() {
    std::shared_ptr<Entity> ent = createEntity();
    ent->addComponent<EntityTypeComponent>()->setType(EntityType::PLAYER);
    return ent;
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
