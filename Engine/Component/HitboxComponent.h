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

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_HITBOXCOMPONENT_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_HITBOXCOMPONENT_H


#include <cstddef>
#include "IComponent.h"

/**
 * @brief Component that defines the hitbox of an entity
 */
class HitboxComponent : public IComponent {
private:
    size_t _width;
    size_t _height;
public:
    HitboxComponent();

    HitboxComponent(size_t width, size_t height);

    size_t getWidth() const;

    [[maybe_unused]] void setWidth(size_t width);

    size_t getHeight() const;

    void setHeight(size_t height);

};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_HITBOXCOMPONENT_H
