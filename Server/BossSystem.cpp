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
#include "Engine/Component/CooldownComponent.h"

void BossSystem::myShoot(std::unique_ptr<Engine> &engine, std::shared_ptr<WeaponComponent> weapon){
    if (weapon->canShoot()) {
        weapon->setNextShot();
        weapon->getWeapon()->shoot(engine, entity);
    }
}

void BossSystem::update(std::unique_ptr<Engine> &engine) {
    auto health = entity->getComponent<HealthComponent>()->getHealth();
    auto maxHealth = entity->getComponent<HealthComponent>()->getMaxHealth();
    auto weapon = entity->getComponent<WeaponComponent>();
    entity->getComponent<PositionComponent>()->setX(500);
    entity->getComponent<PositionComponent>()->setY(500);
    if (weapon) {
        if (health <= maxHealth * 0.75) {
            //change weapon
            myShoot(engine,weapon);
        } else if (health <= maxHealth * 0.50) {

        } else if (health <= maxHealth * 0.25) {

        } else {
            myShoot(engine,weapon);

        }
    }
}

BossSystem::BossSystem(const std::shared_ptr<Entity> &entity) : entity(entity) {}
