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

#include "LuaEntityType.h"

LuaEntityType::LuaEntityType(const std::string &id, size_t hitboxWidth, size_t hitboxHeight, size_t maxHealth,
                             size_t invincibilityTime) : _id(id), _hitboxWidth(hitboxWidth),
                                                         _hitboxHeight(hitboxHeight), _maxHealth(maxHealth),
                                                         _invincibilityTime(invincibilityTime) {}

const std::string &LuaEntityType::getId() const {
    return _id;
}

size_t LuaEntityType::getHitboxWidth() const {
    return _hitboxWidth;
}

size_t LuaEntityType::getHitboxHeight() const {
    return _hitboxHeight;
}

size_t LuaEntityType::getMaxHealth() const {
    return _maxHealth;
}

size_t LuaEntityType::getInvincibilityTime() const {
    return _invincibilityTime;
}
