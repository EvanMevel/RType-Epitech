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

Weapon::Weapon(const std::string &projectile, size_t cooldown) : _projectile(projectile), _cooldown(cooldown) {

}

void Weapon::shoot(std::unique_ptr<Engine> &engine, std::shared_ptr<Entity> shooter) {
    auto typeFactory = engine->getModule<LuaEntityTypeFactory>();
    auto pos = shooter->getComponent<PositionComponent>();
    auto team = shooter->getComponent<TeamComponent>();

    if (!pos || !team) {
        return;
    }
    auto proj = engine->getScene()->unsafeCreateEntity(engine, _projectile, pos->x, pos->y);

    proj->addComponent<TeamComponent>(team->getTeam());
}
