//
// Created by evans on 31/01/2023.
//

#include "EntityUtils.h"

void entity::initPlayer(std::shared_ptr<Entity> entity, int x, int y) {
    entity->addComponent<EntityTypeComponent>()->setType(EntityType::PLAYER);
    auto pos = entity->addComponent<PositionComponent>();
    pos->setX(x);
    pos->setY(y);
    auto physic = entity->addComponent<AccelerationPhysicComponent>();
    physic->maxVelocity = 15;
}

void entity::initProjectile(std::shared_ptr<Entity> entity, int x, int y) {
    entity->addComponent<EntityTypeComponent>()->setType(EntityType::PROJECTILE);
    auto pos = entity->addComponent<PositionComponent>();
    pos->setX(x);
    pos->setY(y);
    auto physic = entity->addComponent<AccelerationPhysicComponent>();
    physic->velocity.x = 10;
    physic->velocitySlow = 0;
}

void entity::initEnemy(std::shared_ptr<Entity> entity, int x, int y) {
    entity->addComponent<EntityTypeComponent>()->setType(EntityType::ENEMY);
    auto pos = entity->addComponent<PositionComponent>();
    pos->setX(x);
    pos->setY(y);
    auto physic = entity->addComponent<AccelerationPhysicComponent>();
}