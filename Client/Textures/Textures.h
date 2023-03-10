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

#ifndef R_TYPE_SERVER_TEXTURES_H
#define R_TYPE_SERVER_TEXTURES_H


#include "Engine/Graphic/IGraphicLib.h"

/**
 * @brief Textures enum
 */
enum class Textures {
    TEXTURE_ERROR = -1,
    TITLE = 0,
    PLAY_BUTTON = 1,
    BACKGROUND_1 = 2,
    BACKGROUND_2 = 3,
    BACKGROUND_3 = 4,
    BACKGROUND_4 = 5,
    BACKGROUND_5 = 6,
    IP_BUTTON = 7,
    HEART = 8,
    EMPTY_HEART = 9,
    CAN_SHOOT = 10,
    CANT_SHOOT = 11,
    BACK_BUTTON = 12,
    QUIT_BUTTON = 13,
    OPTION_BUTTON = 14,
    ARROW_LEFT = 15,
    ARROW_RIGHT = 16,
};

/**
 * @brief Load all textures
 * @param lib Graphic library
 */
void loadTextures(const std::shared_ptr<IGraphicLib> &lib);

#endif //R_TYPE_SERVER_TEXTURES_H
