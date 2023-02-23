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

#include "LuaEntityTypeFactory.h"
#include "Engine/Component/HitboxComponent.h"
#include "Engine/Component/EntityTypeComponent2.h"

std::shared_ptr<LuaEntityType> LuaEntityTypeFactory::addEntityType(const LuaEntityType &entityType) {
    auto type = std::make_shared<LuaEntityType>(entityType);
    _entityTypes.push_back(type);
    return type;
}

void LuaEntityTypeFactory::initEntity(std::shared_ptr<Entity> entity, const std::string &entityType) {
    for (auto &type : _entityTypes) {
        if (type->getId() == entityType) {
            entity->addComponent<EntityTypeComponent2>(type->getId());

            entity->addComponent<HitboxComponent>(type->getHitboxWidth(), type->getHitboxHeight());

            for (auto &component : type->getComponents()) {
                _componentFactory.initComponent(component.first, entity, component.second);
            }
            return;
        }
    }
}

LuaComponentFactory &LuaEntityTypeFactory::getComponentFactory() {
    return _componentFactory;
}

std::shared_ptr<LuaEntityType> LuaEntityTypeFactory::getEntityType(const std::string &entityType) {
    for (auto &type : _entityTypes) {
        if (type->getId() == entityType) {
            return type;
        }
    }
    throw std::runtime_error("Entity type " + entityType + " not found");
}

[[maybe_unused]] int luaRegisterEntityType(lua_State *L) {
    LuaEntityTypeFactory *factory = (LuaEntityTypeFactory*) lua_touserdata(L, 1);

    std::size_t len;
    std::string id = lua_tolstring(L, 2, &len);

    std::size_t hitboxWidth = lua_tointeger(L, 3);
    std::size_t hitboxLength = lua_tointeger(L, 4);

    auto type = factory->addEntityType(LuaEntityType(id, hitboxWidth, hitboxLength));

    lua_pushlightuserdata(L, type.get());
    luaL_setmetatable(L, "LuaEntityType");

    return 1;
}

[[maybe_unused]] int luaAddComponentToType(lua_State *L) {
    int argc = lua_gettop(L);
    LuaEntityType *type = (LuaEntityType*) luaL_checkudata(L, 1, "LuaEntityType");

    std::string component = lua_tostring(L, 2);

    std::vector<int> args;

    for (size_t i = 3; i <= argc; i++) {
        args.push_back(lua_tointeger(L, i));
    }

    type->addComponent(component, args);

    return 0;
}
