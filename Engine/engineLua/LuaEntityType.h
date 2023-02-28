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

#ifndef R_TYPE_SERVER_LUAENTITYTYPE_H
#define R_TYPE_SERVER_LUAENTITYTYPE_H

#include "LuaWrapper.h"

class LuaEntityType {
private:
    std::string _id;
    std::size_t _hitboxWidth;
    std::size_t _hitboxHeight;
    std::vector<std::pair<std::string, std::vector<std::any>>> _components;
public:
    LuaEntityType(const std::string &id, size_t hitboxWidth, size_t hitboxHeight);

    const std::string &getId() const;

    size_t getHitboxWidth() const;

    size_t getHitboxHeight() const;

    void addComponent(const std::string &name, const std::vector<std::any> &args);

    const std::vector<std::pair<std::string, std::vector<std::any>>> &getComponents() const;
};


#endif //R_TYPE_SERVER_LUAENTITYTYPE_H
