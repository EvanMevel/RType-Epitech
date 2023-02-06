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

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_HEALTHCOMPONENT_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_HEALTHCOMPONENT_H

#include <cstddef>
#include "IComponent.h"

/**
 * @brief Component that defines the health of an entity
 */
class HealthComponent : public IComponent {
private:
    size_t health;
    unsigned long long lastDamageTime = 0;
    size_t invincibilityTime = 0;
public:
    void setHealth(size_t health);

    void damage(size_t damage);

    bool isAlive() const;

    void setInvincibilityTime(size_t invincibilityTime);

    bool isInvincible() const;
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_HEALTHCOMPONENT_H
