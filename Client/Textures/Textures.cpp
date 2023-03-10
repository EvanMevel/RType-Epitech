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

#include "Textures.h"

void loadTextures(const std::shared_ptr<IGraphicLib> &lib) {
    lib->registerTexture(Textures::TITLE, "rtype.png");
    lib->registerTexture(Textures::PLAY_BUTTON, "play_button.png");
    lib->registerTexture(Textures::IP_BUTTON, "play_button.png");
    lib->registerTexture(Textures::OPTION_BUTTON, "settings_button.png");
    lib->registerTexture(Textures::QUIT_BUTTON, "quit_button.png");
    lib->registerTexture(Textures::BACK_BUTTON, "back_button.png");

    lib->registerTexture(Textures::BACKGROUND_1, "Starry background  - Layer 01 - Solid colour.png");
    lib->registerTexture(Textures::BACKGROUND_2, "Starry background  - Layer 02 - Shadows.png");
    lib->registerTexture(Textures::BACKGROUND_3, "Starry background  - Layer 02 - Shadows 2.png");
    lib->registerTexture(Textures::BACKGROUND_4, "Starry background  - Layer 03 - Stars.png");
    lib->registerTexture(Textures::BACKGROUND_5, "Starry background  - Layer 03 - Stars 2.png");

    lib->registerTexture(Textures::HEART, "heart.png");
    lib->registerTexture(Textures::EMPTY_HEART, "empty_heart.png");
    lib->registerTexture(Textures::CAN_SHOOT, "can_shoot.png");
    lib->registerTexture(Textures::CANT_SHOOT, "cant_shoot.png");

    lib->registerTexture(Textures::ARROW_LEFT, "arrow_left.png");
    lib->registerTexture(Textures::ARROW_RIGHT, "arrow_right.png");
}