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

#include "PacketSendingScene.h"
#include "Engine/Network/Packets/EntityDestroyPacket.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"
#include "Engine/Component/InanimateComponent.h"
#include "Engine/Component/ColliderComponent.h"
#include "Engine/Component/PhysicComponent.h"

PacketSendingScene::PacketSendingScene(EntityManager &entityManager, const RTypeServerPtr &server) : Scene(
        entityManager), server(server) {}

void PacketSendingScene::removeEntity(std::shared_ptr<Entity> entity) {
    Scene::removeEntity(entity);
    EntityDestroyPacket packet(entity->getId());
    server->broadcast(packet);
}

void PacketSendingScene::removeEntity(EntityId entityId) {
    Scene::removeEntity(entityId);
    EntityDestroyPacket packet(entityId);
    server->broadcast(packet);
}

void PacketSendingScene::filterEntities(std::function<bool(std::shared_ptr<Entity>)> filter) {
    std::lock_guard<std::mutex> lock(entityMutex);
    entities.erase(
            std::remove_if(entities.begin(), entities.end(), [&](std::shared_ptr<Entity> &entity) {
                if (entity == nullptr)
                    return false;
                if (filter(entity)) {
                    EntityDestroyPacket packet(entity->getId());
                    server->broadcast(packet);
                    return true;
                }
                return false;
            }),
            entities.end()
    );
}

void PacketSendingScene::filterEntities(std::function<bool(std::shared_ptr<Entity>, EnginePtr)> filter,
                                        std::unique_ptr<Engine> &engine) {
    std::lock_guard<std::mutex> lock(entityMutex);
    entities.erase(
            std::remove_if(entities.begin(), entities.end(), [&](std::shared_ptr<Entity> &entity) {
                if (entity == nullptr)
                    return false;
                if (filter(entity, engine)) {
                    EntityDestroyPacket packet(entity->getId());
                    server->broadcast(packet);
                    return true;
                }
                return false;
            }),
            entities.end()
    );
}

CollideResult mooveOther(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other) {
    if (other->hasComponent<InanimateComponent>()) {
        return CollideResult::NONE;
    }
    auto type = other->getComponent<EntityTypeComponent>();

    if (type != nullptr && type->getEntityType() == "player") {
        other->getComponent<PhysicComponent>()->acceleration.x = -5;
    }
    return CollideResult::NONE;
}

std::shared_ptr<Entity> PacketSendingScene::createEntity(std::unique_ptr<Engine> &engine, const std::string &type, int x, int y) {
    auto entity = Scene::createEntity(engine, type, x, y);

    if (entity->hasComponent<InanimateComponent>()) {
        entity->addComponent<ColliderComponent>(mooveOther);
    }

    EntityInfoPacket newEntityPacket(entity);
    server->broadcast(newEntityPacket);
    return entity;
}

std::shared_ptr<Entity> PacketSendingScene::unsafeCreateEntity(std::unique_ptr<Engine> &engine, const std::string &type, int x, int y) {
    auto entity = Scene::unsafeCreateEntity(engine, type, x, y);

    EntityInfoPacket newEntityPacket(entity);
    server->broadcast(newEntityPacket);
    return entity;
}
