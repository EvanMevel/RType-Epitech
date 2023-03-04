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

#include "BossSystem.h"
#include "Engine/Component/HealthComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Engine/TickUtil.h"
#include "RTypeServer.h"
#include "Engine/Component/PhysicComponent.h"
#include "Engine/Component/EntityTypeComponent2.h"

void BossSystem::myShoot(std::unique_ptr<Engine> &engine, std::shared_ptr<WeaponComponent> weapon){
    if (weapon->canShoot()) {
        weapon->setNextShot();
        weapon->getWeapon()->shoot(engine, _entity);
    }
}

void BossSystem::update(std::unique_ptr<Engine> &engine) {
    if (_entity == nullptr){
        std::function<void(std::shared_ptr<Entity>)> setter = std::bind(&BossSystem::setEntity, this, std::placeholders::_1);
        std::function<void(std::shared_ptr<Entity> entity, EnginePtr engine)> f = [setter](std::shared_ptr<Entity> entity, EnginePtr engine) {
            auto type = entity->getComponent<EntityTypeComponent2>();
            if (type == nullptr || type->getEntityType().find("BOSS") == std::string::npos) {
                return;
            }
            setter(entity);
        };
        engine->getScene()->forEachEntity(f, engine);
        return;
    }
    auto healthComponent = _entity->getComponent<HealthComponent>();
    auto health = healthComponent->getHealth();
    if (!healthComponent->isAlive()){
        return;
    }
    auto maxHealth = healthComponent->getMaxHealth();
    auto weaponComponent = _entity->getComponent<WeaponComponent>();
    _entity->getComponent<PositionComponent>()->setY(120);
    auto physicComponent = _entity->getComponent<PhysicComponent>();
    if(_entity->getComponent<PositionComponent>()->getX() > 1500){
        physicComponent->velocity.x = -2;
    }
    auto ticker = engine->getModule<TickUtil>();
    EntityVelocityPacket packet(_entity, ticker->getCurrentTick());
    engine->getModule<RTypeServer>()->broadcast(packet);
    if (health <= maxHealth * 0.10) {
        if (currentStage != 4){
            currentStage = 4;
            currentWeapon = _weaponStage4;
            weaponComponent->setWeapon(currentWeapon);
        }
        myShoot(engine,weaponComponent);
    } else if (health <= maxHealth * 0.50) {
        if (currentStage != 3){
            currentStage = 3;
            currentWeapon = _weaponStage3;
            weaponComponent->setWeapon(currentWeapon);
        }
        myShoot(engine,weaponComponent);
    } else if (health <= maxHealth * 0.75) {
        if (currentStage != 2){
            currentStage = 2;
            currentWeapon = _weaponStage2;
            weaponComponent->setWeapon(currentWeapon);
        }
        myShoot(engine,weaponComponent);
    } else {
        if (currentStage != 1){
            currentStage = 1;
            currentWeapon = _weaponStage1;
            weaponComponent->setWeapon(currentWeapon);
        }
        myShoot(engine,weaponComponent);
    }
}

void BossSystem::setEntity(const std::shared_ptr<Entity> &entity) {
    _entity = entity;
}

BossSystem::BossSystem(){
    _weaponStage1 = createWeapon<SynchronizedWeaponBossStage2>("projectile2",(size_t)(ENGINE_TPS),4);
    _weaponStage2 = createWeapon<SynchronizedWeaponBossStage2>("projectile2",(size_t)(ENGINE_TPS/1.5),8);
    _weaponStage3 = createWeapon<SynchronizedWeaponBossStage2>("projectile2",(size_t)(ENGINE_TPS/2),12);
    _weaponStage4 = createWeapon<SynchronizedWeaponBossStage2>("projectile2",(size_t)(ENGINE_TPS/2.5),16);
}

void SynchronizedWeaponBossStage2::shoot(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> shooter) {
    auto posShooter = shooter->getComponent<PositionComponent>();
    for (size_t i = 1; i <= _howMany; i++){
        shootAtPos(engine, shooter, posShooter->getX(), posShooter->getY() + (i-1)*50);
    }
}

SynchronizedWeaponBossStage2::SynchronizedWeaponBossStage2(const std::string &projectile, size_t cooldown, size_t howMany)
        : SynchronizedWeapon(projectile, cooldown) {
    _howMany = howMany;
}

CollideResult SynchronizedWeaponBossStage2::projectileHit(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> self,
                                                          std::shared_ptr<Entity> other) {
    return SynchronizedWeapon::projectileHit(engine, self, other);
}

void SynchronizedWeaponBossStage2::onDamage(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> cause,
                                            std::shared_ptr<Entity> victim, int damage) {
    SynchronizedWeapon::onDamage(engine, cause, victim, damage);
}
