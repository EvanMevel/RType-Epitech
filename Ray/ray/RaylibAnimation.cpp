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

#include "RaylibAnimation.h"
/**
 * @brief Set every parameter which is needed for the draw function
 */
RaylibAnimation::RaylibAnimation(const std::string &texturePath) {
    const char *c = texturePath.c_str();
    image = ray::LoadImageAnim(c,&frame);
    texture = ray::LoadTextureFromImage(std::any_cast<ray::Image>(image));
    width = std::any_cast<ray::Image>(image).width;
    height = std::any_cast<ray::Image>(image).height;
}
/**
 * @brief change the animation frame
 */
void RaylibAnimation::setAnimationFrame(int frame) {
    int nextFrameAnim = width * height * 4 * frame;
    ray::UpdateTexture(std::any_cast<ray::Texture2D>(texture), ((unsigned char *)std::any_cast<ray::Image>(image).data) + nextFrameAnim);
}
