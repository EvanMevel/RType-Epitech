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

#include "ScrollingTextureComponent.h"

int ScrollingTextureComponent::getScroll() const {
    return scroll;
}

void ScrollingTextureComponent::setScroll(int scroll) {
    ScrollingTextureComponent::scroll = scroll;
}

int ScrollingTextureComponent::getScrollingSpeed() const {
    return scrollingSpeed;
}

void ScrollingTextureComponent::setScrollingSpeed(int scrollingSpeed) {
    ScrollingTextureComponent::scrollingSpeed = scrollingSpeed;
}

void ScrollingTextureComponent::applySpeed() {
    scroll += scrollingSpeed;
    scroll %= width;
}

float ScrollingTextureComponent::getScale() const {
    return scale;
}

void ScrollingTextureComponent::setScale(float scale) {
    ScrollingTextureComponent::scale = scale;
}

void ScrollingTextureComponent::setWidth(int width) {
    ScrollingTextureComponent::width = width;
}
