//
// Created by aaama on 17/01/2023.
//

#include "Scene.h"
#include "Engine.h"
#include "EntityTypeComponent.h"

void Scene::update(Engine &engine) {
    for (auto &sys: systems) {
        sys->update(engine);
    }
}

void Scene::addEntity(Entity &entity) {
    this->entities.push_back(entity);
}

Scene::~Scene() {
    for (const auto &sys: systems) {
        delete sys;
    }
}

void Scene::addSystem(ISystem *sys) {
    this->systems.push_back(sys);
}

std::vector<Entity> &Scene::getEntities() {
    return this->entities;
}

Entity &Scene::createEntity(Engine &engine) {
    this->entities.push_back(engine.createEntity());
    return this->entities.back();
}

Entity &Scene::createPlayer(Engine &engine) {
    Entity &ent = createEntity(engine);
    ent.addComponent<EntityTypeComponent>()->setType(EntityType::PLAYER);
    return ent;
}
