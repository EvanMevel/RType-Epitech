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

void projectileHit(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other,
                   std::unordered_map<size_t, std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>>>> &teams) {
    std::cout << "Projectile " << self->getId() << " hit " << other->getId() << std::endl;
}

void entity::initProjectile(std::shared_ptr<Entity> entity, int x, int y, int velX) {
    entity->addComponent<EntityTypeComponent>()->setType(EntityType::PROJECTILE);
    auto pos = entity->addComponent<PositionComponent>();
    pos->setX(x);
    pos->setY(y);
    auto physic = entity->addComponent<AccelerationPhysicComponent>();
    physic->velocity.x = velX;
    physic->velocitySlow = 0;

    auto collider = entity->addComponent<ColliderComponent>();
    collider->_onCollision = projectileHit;

    auto hitbox = entity->addComponent<HitboxComponent>();
    hitbox->setLengthX(50);
    hitbox->setLengthY(20);
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