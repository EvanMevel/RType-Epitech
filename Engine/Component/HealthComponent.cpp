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

#include "HealthComponent.h"
#include "TimeUtil.h"

HealthComponent::HealthComponent() : _health(0),
                                     _maxHealth(0) {

}

HealthComponent::HealthComponent(size_t health) : _health(health),
                                                  _maxHealth(health) {

}

HealthComponent::HealthComponent(size_t health, size_t invincibilityTime) : _health(health),
                                                                            _invincibilityTime(invincibilityTime),
                                                                            _maxHealth(health) {

}

void HealthComponent::damage(size_t damage) {
    _lastDamageTime = getCurrentTime();
    if (_health > damage) {
        _health -= damage;
    } else {
        _health = 0;
    }
}

bool HealthComponent::isAlive() const {
    return _health > 0;
}

bool HealthComponent::isInvincible() const {
    return _lastDamageTime + _invincibilityTime > getCurrentTime();
}

[[maybe_unused]] void HealthComponent::setInvincibilityTime(size_t time) {
    _invincibilityTime = time;
}

[[maybe_unused]] void HealthComponent::setHealth(size_t health) {
    _health = health;
}

size_t HealthComponent::getMaxHealth() const {
    return _maxHealth;
}

size_t HealthComponent::getHealth() const {
    return _health;
}
