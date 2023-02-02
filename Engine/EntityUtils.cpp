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

    auto hitbox = entity->addComponent<HitboxComponent>();
    hitbox->setLengthX(50);
    hitbox->setLengthY(50);

    auto tim = entity->addComponent<TeamComponent>();
    tim->setTeam(0);
}

void entity::initProjectile(std::shared_ptr<Entity> entity, int x, int y, int velX) {
    entity->addComponent<EntityTypeComponent>()->setType(EntityType::PROJECTILE);
    auto pos = entity->addComponent<PositionComponent>();
    pos->setX(x);
    pos->setY(y);
    auto physic = entity->addComponent<AccelerationPhysicComponent>();
    physic->velocity.x = velX;
    physic->velocitySlow = 0;
}

void entity::initEnemy(std::shared_ptr<Entity> entity, int x, int y) {
    entity->addComponent<EntityTypeComponent>()->setType(EntityType::ENEMY);
    auto pos = entity->addComponent<PositionComponent>();
    pos->setX(x);
    pos->setY(y);
    auto physic = entity->addComponent<AccelerationPhysicComponent>();

    auto team = entity->addComponent<TeamComponent>();
    team->setTeam(1);

    auto hitbox = entity->addComponent<HitboxComponent>();
    hitbox->setLengthX(50);
    hitbox->setLengthY(50);
}