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

#include "LuaWrapper.h"

LuaWrapper::LuaWrapper() {
    L = luaL_newstate();
    luaL_openlibs(L);
}

LuaWrapper::~LuaWrapper() {
    lua_close(L);
}

int LuaWrapper::doFile(const std::string &filename) {
    return luaL_dofile(L, filename.c_str());
}

void LuaWrapper::registerFunction(std::string name, lua_CFunction func) {
    lua_register(L, name.c_str(), func);
}

void LuaWrapper::defineGlobal(std::string name, int value) {
    lua_pushinteger(L, value);
    lua_setglobal(L, name.c_str());
}

lua_State *LuaWrapper::getLuaState() const {
    return L;
}

void LuaWrapper::newMetaTable(const std::string &name) {
    luaL_newmetatable(L, name.c_str());
}
