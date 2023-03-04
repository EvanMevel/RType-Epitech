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

#ifndef R_TYPE_SERVER_BOSSSYSTEM_H
#define R_TYPE_SERVER_BOSSSYSTEM_H


#include "Engine/ISystem.h"
#include "Engine/Entity.h"
#include "Engine/Component/WeaponComponent.h"
#include "SynchronizedWeapon.h"

class BossSystem : public ISystem {
private:
    size_t currentStage = 0;
    std::shared_ptr<Weapon> currentWeapon = _weaponStage1;
    std::shared_ptr<Entity> _entity;
    std::shared_ptr<Weapon> _weaponStage1;
    std::shared_ptr<Weapon> _weaponStage2;
    std::shared_ptr<Weapon> _weaponStage3;
    std::shared_ptr<Weapon> _weaponStage4;

public:
    void update(std::unique_ptr<Engine> &engine) override;

    void myShoot(std::unique_ptr<Engine> &engine, std::shared_ptr<WeaponComponent> weapon);

    explicit BossSystem();

    void setEntity(const std::shared_ptr<Entity> &entity);

    template<class WeaponType, class ...Args>
    std::shared_ptr<Weapon> createWeapon(Args&&... args){
        return std::make_shared<WeaponType>(args...);
    }
};

class SynchronizedWeaponBossStage2 : public SynchronizedWeapon {
private:
    size_t _howMany;
public:
    void shoot(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> shooter) override;

    CollideResult projectileHit(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> self,
                                std::shared_ptr<Entity> other) override;

    void onDamage(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> cause, std::shared_ptr<Entity> victim,
                  int damage) override;

    SynchronizedWeaponBossStage2(const std::string &projectile, size_t cooldown, size_t howMany);
};

#endif //R_TYPE_SERVER_BOSSSYSTEM_H
