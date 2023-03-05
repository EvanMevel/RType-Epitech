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

#include "Weapon.h"
#include "Engine.h"
#include "engineLua/LuaEntityTypeFactory.h"
#include "PositionComponent.h"
#include "TeamComponent.h"
#include "EntityTypeComponent2.h"
#include "HealthComponent.h"
#include "PhysicComponent.h"
#include "CollectableComponent.h"

Weapon::Weapon(const std::string &projectile, size_t cooldown, int velX, int velY) : _projectile(projectile),
                                                                                     _cooldown(cooldown), velX(velX),
                                                                                     velY(velY) {

    _projectileHit = std::bind(&Weapon::projectileHit, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void Weapon::shootAtPos(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> shooter, int x, int y){
    auto typeFactory = engine->getModule<LuaEntityTypeFactory>();
    auto team = shooter->getComponent<TeamComponent>();

    if (!team) {
        return;
    }
    auto projectile = engine->getScene()->unsafeCreateEntity(engine, _projectile, x, y);

    projectile->getComponent<PhysicComponent>()->velocity = Vector2i(velX, velY);

    projectile->addComponent<ColliderComponent>(_projectileHit);

    projectile->addComponent<TeamComponent>(team->getTeam());

}

void Weapon::shoot(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> shooter) {
    auto pos = shooter->getComponent<PositionComponent>();

    if (!pos) {
        return;
    }
    shootAtPos(engine, shooter, pos->getX(), pos->getY() + 20);
}

void Weapon::onDamage(EnginePtr engine, std::shared_ptr<Entity> cause, std::shared_ptr<Entity> victim, int damage) {

}

CollideResult Weapon::projectileHit(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other) {
    auto otherTeam = other->getComponent<TeamComponent>();
    auto selfTeam = self->getComponent<TeamComponent>();

    if (selfTeam == nullptr || (otherTeam != nullptr && selfTeam->getTeam() == otherTeam->getTeam()) || other->hasComponent<CollectableComponent>()) {
        return CollideResult::NONE;
    }

    engine->getScene()->removeEntity(self);

    auto health = other->getComponent<HealthComponent>();

    if (health != nullptr) {
        if (!health->isInvincible()) {
            health->damage(10);
            onDamage(engine, self, other, 10);
            if (!health->isAlive()) {
                engine->getScene()->removeEntity(other);
                return CollideResult::BOTH_REMOVED;
            } else {
                return CollideResult::SOURCE_REMOVED;
            }
        }
    } else {
        auto otherType = other->getComponent<EntityTypeComponent2>();
        if (otherType != nullptr && otherType->getEntityType().find("projectile") != std::string::npos) {
            engine->getScene()->removeEntity(other);
            return CollideResult::BOTH_REMOVED;
        }
        return CollideResult::SOURCE_REMOVED;
    }
    return CollideResult::SOURCE_REMOVED;
}

size_t Weapon::getCooldown() const {
    return _cooldown;
}
