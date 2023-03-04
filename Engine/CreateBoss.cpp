//
// Created by aaama on 03/03/2023.
//

#include "CreateBoss.h"
#include "HealthComponent.h"
#include "PhysicComponent.h"
#include "HitboxComponent.h"
#include "EntityTypeComponent2.h"
#include "WeaponComponent.h"
#include "engineLua/LuaWeaponFactory.h"
#include "TeamComponent.h"
#include "CooldownComponent.h"

void BossCreator::createBoss(EnginePtr engine,std::shared_ptr <Entity> entity) {
    entity->addComponent<PhysicComponent>();
    entity->addComponent<HealthComponent>(400);
    entity->addComponent<HitboxComponent>(143*3,260*3);
    entity->addComponent<EntityTypeComponent2>("BOSS");
    entity->addComponent<TeamComponent>(1);
    entity->addComponent<CooldownComponent>();
    auto weaponFactory = engine->getModule<LuaWeaponFactoryBase>();
    auto weapon = weaponFactory->getWeapon("weapon2");
    entity->addComponent<WeaponComponent>(weapon);
}
