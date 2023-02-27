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

#ifndef R_TYPE_SERVER_LUAENTITYTYPEFACTORY_H
#define R_TYPE_SERVER_LUAENTITYTYPEFACTORY_H

#include <iostream>
#include "LuaEntityType.h"
#include "Engine/Entity.h"
#include "LuaComponentFactory.h"

class LuaEntityTypeFactory {
private:
    std::vector<std::shared_ptr<LuaEntityType>> _entityTypes;
    LuaComponentFactory _componentFactory;

public:
    LuaEntityTypeFactory() = default;

    std::shared_ptr<LuaEntityType> addEntityType(const LuaEntityType &entityType);

    void initEntity(std::shared_ptr<Entity> entity, const std::string &entityType);

    LuaComponentFactory &getComponentFactory();

    std::shared_ptr<LuaEntityType> getEntityType(const std::string &entityType);
};

[[maybe_unused]] int luaRegisterEntityType(lua_State *L);

[[maybe_unused]] int luaAddComponentToType(lua_State *L);

#endif //R_TYPE_SERVER_LUAENTITYTYPEFACTORY_H
