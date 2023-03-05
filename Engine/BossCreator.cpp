//
// Created by aaama on 03/03/2023.
//

#include "BossCreator.h"
#include "HealthComponent.h"
#include "PhysicComponent.h"
#include "HitboxComponent.h"
#include "EntityTypeComponent.h"
#include "WeaponComponent.h"
#include "engineLua/LuaWeaponFactory.h"
#include "TeamComponent.h"

void BossCreator::createBoss(EnginePtr engine,std::shared_ptr <Entity> entity) {
    entity->addComponent<PhysicComponent>();
    entity->addComponent<HealthComponent>(400);
    entity->addComponent<HitboxComponent>(143*3,260*3);
    entity->addComponent<EntityTypeComponent>("BOSS");
    entity->addComponent<TeamComponent>(1);
    auto weaponFactory = engine->getModule<LuaWeaponFactoryBase>();
    entity->addComponent<WeaponComponent>();
}
