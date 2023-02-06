// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

std::shared_ptr<Entity> Scene::getOrCreateEntityById(size_t id) {
    for (auto &ent: entities) {
        if (ent->getId() == id) {
            return ent;
        }
    }
    std::shared_ptr<Entity> ent = std::make_shared<Entity>(id);
    entities.push_back(ent);
    return entities.back();
}

std::shared_ptr<Entity> Scene::getEntityById(size_t id) {
    for (auto &ent: entities) {
        if (ent->getId() == id) {
            return ent;
        }
    }
    return nullptr;
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
