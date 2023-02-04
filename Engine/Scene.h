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
