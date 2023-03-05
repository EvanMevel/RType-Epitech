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

#ifndef R_TYPE_SERVER_LUAWRAPPER_H
#define R_TYPE_SERVER_LUAWRAPPER_H

#include <string>
#include <map>
#include <unordered_map>
#include <typeindex>
#include <utility>
#include <vector>
#include <any>
#include "LuaType.h"

extern "C" {
    #include "Engine/lua/lua-5.4.4/include/lua.h"
    #include "Engine/lua/lua-5.4.4/include/lualib.h"
    #include "Engine/lua/lua-5.4.4/include/lauxlib.h"
}

/**
 * @brief Class that represent the keywork void in Lua
 */
class VoidType {};

/*
 * @brief Class that allows to call a Lua function
 */
template<class Ret, class ...Args>
class LuaFunction {
private:
    lua_State* L;
    std::string _name;
public:
    LuaFunction(lua_State *l, std::string name) : L(l), _name(std::move(name)) {}

    Ret call(Args... args) {
        const std::size_t n = sizeof...(Args);
        lua_getglobal(L, _name.c_str());
        std::vector<std::any> vec = {args...};
        for (int i = 0; i < n; ++i) {
            if (vec[i].type() == typeid(int)) {
                lua_pushinteger(L, std::any_cast<int>(vec[i]));
            } else if (vec[i].type() == typeid(float)) {
                lua_pushnumber(L, std::any_cast<float>(vec[i]));
            } else if (vec[i].type() == typeid(std::string)) {
                lua_pushstring(L, std::any_cast<std::string>(vec[i]).c_str());
            } else if (vec[i].type() == typeid(bool)) {
                lua_pushboolean(L, std::any_cast<bool>(vec[i]));
            } else if (vec[i].type() == typeid(void*)) {
                lua_pushlightuserdata(L, std::any_cast<void*>(vec[i]));
            } else if (vec[i].type() == typeid(LuaType)) {
                LuaType t = std::any_cast<LuaType>(vec[i]);
                lua_pushlightuserdata(L, t.getPtr());

                luaL_setmetatable(L, t.getName().c_str());
            }
        }
        std::any value;
        if (typeid(Ret) == typeid(VoidType)) {
            lua_call(L, (int) n, 0);
            value = VoidType();
        } else {
            lua_call(L, (int) n, 1);
            if (typeid(Ret) == typeid(int)) {
                value = (int) lua_tointeger(L, -1);
            } else if (typeid(Ret) == typeid(float)) {
                value = (float) lua_tonumber(L, -1);
            } else if (typeid(Ret) == typeid(std::string)) {
                value = std::string(lua_tostring(L, -1));
            } else if (typeid(Ret) == typeid(bool)) {
                value = (bool) lua_toboolean(L, -1);
            } else if (typeid(Ret) == typeid(void*)) {
                value = lua_touserdata(L, -1);
            }
            lua_pop(L, 1);
        }
        return std::any_cast<Ret>(value);
    }
};

/**
 * @brief Class that allows to call a lua functions
 */
class LuaWrapper {
private:
    lua_State* L;

public:
    LuaWrapper();

    virtual ~LuaWrapper();

    int doFile(const std::string& filename);

    template<class ...Args>
    LuaFunction<Args...> getFunction(std::string name) {
        return LuaFunction<Args...>(L, std::move(name));
    }

    void registerFunction(std::string name, lua_CFunction func);

    void defineGlobal(std::string name, int value);

    lua_State *getLuaState() const;

    void newMetaTable(const std::string &name);

};

#endif //R_TYPE_SERVER_LUAWRAPPER_H
