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

#ifndef R_TYPE_CLIENT_LUALEVELFACTORY_H
#define R_TYPE_CLIENT_LUALEVELFACTORY_H

#include "Engine/Level.h"
#include "LuaWrapper.h"

class LuaLevelFactory {
private:
    std::vector<std::shared_ptr<Level>> _levels;

public:
    std::shared_ptr<Level> createLevel(const std::string &name);

    const std::vector<std::shared_ptr<Level>> &getLevels() const;
};

[[maybe_unused]] int luaCreateLevel(lua_State *L);

[[maybe_unused]] int luaAddEnemyToLevel(lua_State *L);

#endif //R_TYPE_CLIENT_LUALEVELFACTORY_H