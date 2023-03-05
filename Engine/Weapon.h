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

#ifndef R_TYPE_CLIENT_WEAPON_H
#define R_TYPE_CLIENT_WEAPON_H

#include "EngineTypes.h"
#include "Engine/EngineTypes.h"
#include "Engine/Component/ColliderComponent.h"

/**
 * @brief Class that defines a weapon to shoot with
 */
class Weapon {
private:
    std::string _projectile;
    std::size_t _cooldown;
    CollideFunction _projectileHit;
    int velX;
    int velY;

public:
    Weapon(const std::string &projectile, size_t cooldown, int velX, int velY);

    virtual std::shared_ptr<Entity> shootAtPos(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> shooter, int x, int y);

    virtual void shoot(EnginePtr engine, std::shared_ptr<Entity> shooter);

    virtual CollideResult projectileHit(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other);

    virtual void onDamage(EnginePtr engine, std::shared_ptr<Entity> cause, std::shared_ptr<Entity> victim, int damage);

    size_t getCooldown() const;
};


#endif //R_TYPE_CLIENT_WEAPON_H
