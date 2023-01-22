//
// Created by aaama on 17/01/2023.
//

#include "Scene.h"
#include "Engine.h"
#include "EntityTypeComponent.h"

Scene::~Scene() {
}

void Scene::addEntity(Entity &entity) {
    this->entities.push_back(entity);
}

std::vector<Entity> &Scene::getEntities() {
    return this->entities;
}

Entity &Scene::createEntity() {
    this->entities.push_back(entityManager.createEntity());
    return this->entities.back();
}

Entity &Scene::createPlayer() {
    Entity &ent = createEntity();
    ent.addComponent<EntityTypeComponent>()->setType(EntityType::PLAYER);
    return ent;
}

Scene::Scene(EntityManager &entityManager) : entityManager(entityManager) {

}
