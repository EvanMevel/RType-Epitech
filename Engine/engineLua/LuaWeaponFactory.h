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

#ifndef R_TYPE_CLIENT_LUAWEAPONFACTORY_H
#define R_TYPE_CLIENT_LUAWEAPONFACTORY_H

#include "Engine/Weapon.h"
#include "Engine/engineLua/LuaWrapper.h"


class LuaWeaponFactoryBase {
protected:
    std::unordered_map<std::string, std::shared_ptr<Weapon>> _weapons;
public:
    virtual void registerWeapon(const std::string &name, const std::string &proj, std::size_t cooldown, int velX, int velY) = 0;

    std::shared_ptr<Weapon> getWeapon(const std::string &name) {
        return _weapons[name];
    }
};

template <class T>
class LuaWeaponFactory : public LuaWeaponFactoryBase {
public:
    void registerWeapon(const std::string &name, const std::string &proj, std::size_t cooldown, int velX, int velY) override {
        _weapons[name] = std::make_shared<T>(proj, cooldown, velX, velY);
    }

};

[[maybe_unused]] int luaRegisterWeapon(lua_State *L);

#endif //R_TYPE_CLIENT_LUAWEAPONFACTORY_H
