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

#include "LuaWeaponFactory.h"


[[maybe_unused]] int luaRegisterWeapon(lua_State *L) {
    LuaWeaponFactoryBase *factory = (LuaWeaponFactoryBase*) lua_touserdata(L, 1);

    std::size_t len;
    std::string name = lua_tolstring(L, 2, &len);
    std::string proj = lua_tolstring(L, 3, &len);

    std::size_t cooldown = lua_tointeger(L, 4);

    int velX = lua_tointeger(L, 5);
    int velY = lua_tointeger(L, 6);

    factory->registerWeapon(name, proj, cooldown, velX, velY);

    return 0;
}