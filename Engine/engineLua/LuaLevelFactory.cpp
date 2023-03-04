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

#include "LuaLevelFactory.h"

std::shared_ptr<Level> LuaLevelFactory::createLevel(const std::string &name) {
    auto level = std::make_shared<Level>(name);
    _levels.push_back(level);
    return level;
}

std::shared_ptr<Level> LuaLevelFactory::createLevel(const std::string &name, std::size_t end) {
    auto level = std::make_shared<Level>(name, end);
    _levels.push_back(level);
    return level;
}

const std::vector<std::shared_ptr<Level>> &LuaLevelFactory::getLevels() const {
    return _levels;
}

[[maybe_unused]] int luaCreateLevel(lua_State *L) {
    int argc = lua_gettop(L);
    LuaLevelFactory *levelList = (LuaLevelFactory*) lua_touserdata(L, 1);

    std::string name = lua_tostring(L, 2);

    std::shared_ptr<Level> level;

    if (argc == 3) {
        int end = lua_tonumber(L, 3);
        level = levelList->createLevel(name, end);
    } else {
        level = levelList->createLevel(name);
    }

    lua_pushlightuserdata(L, level.get());
    luaL_setmetatable(L, "LuaLevel");

    return 1;
}

[[maybe_unused]] int luaAddObjectToLevel(lua_State *L) {
    Level *level = (Level*) luaL_checkudata(L, 1, "LuaLevel");

    std::string type = lua_tostring(L, 2);
    int x = lua_tonumber(L, 3);
    int y = lua_tonumber(L, 4);

    level->addObject(type, x, y);
    return 0;
}
