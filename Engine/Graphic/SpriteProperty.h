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

#ifndef R_TYPE_SERVER_SPRITEPROPERTY_H
#define R_TYPE_SERVER_SPRITEPROPERTY_H

#include <memory>
#include "Engine/Rectangle.h"
#include "ITexture.h"

class Sprite;

/**
 * @brief Sprite class
 */
class SpriteProperty {
public:
    std::shared_ptr<ITexture> texture;
    int startX;
    int startY;

    int lengthX;
    int lengthY;

    int repeatX;
    int repeatY;

    std::size_t frameSpeed;

    float scale = 1.0f;

    SpriteProperty(const std::shared_ptr<ITexture> &texture, int startX, int startY, int lengthX, int lengthY, int repeatX,
                   int repeatY, std::size_t frameSpeed);

    SpriteProperty(const std::shared_ptr<ITexture> &texture, int startX, int startY, int lengthX, int lengthY, int repeatX,
                   int repeatY, std::size_t frameSpeed, float scale);

    std::shared_ptr<Sprite> createSprite(std::shared_ptr<SpriteProperty> spriteProperty);

    void updateRect(std::size_t &currentFrame, Rectangle &rect);
};


#endif //R_TYPE_SERVER_SPRITEPROPERTY_H
