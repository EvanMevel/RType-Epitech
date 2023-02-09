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

#include "Vector2i.h"

static void absoluteVarTo0(int &var, size_t i) {
    if (var < 0) {
        var = (int) (var + i);
        if (var > 0) {
            var = 0;
        }
    } else {
        var = (int) (var - i);
        if (var < 0) {
            var = 0;
        }
    }
}

static void ensureNotGreater(int &var, int max) {
    if (var > max) {
        var = max;
    }
    if (var < -max) {
        var = -max;
    }
}

Vector2i::Vector2i() : x(0), y(0) {

}

Vector2i::Vector2i(int x, int y) : x(x), y(y) {

}

int Vector2i::getX() const {
    return x;
}

void Vector2i::setX(int ox) {
    Vector2i::x = ox;
}

int Vector2i::getY() const {
    return y;
}

void Vector2i::setY(int oy) {
    Vector2i::y = oy;
}

void Vector2i::operator+=(const Vector2i &other) {
    x += other.x;
    y += other.y;
}

void Vector2i::decrementTo0(size_t decr) {
    ::absoluteVarTo0(x, decr);
    ::absoluteVarTo0(y, decr);
}

Vector2i Vector2i::clone() const {
    return Vector2i(x, y);
}

size_t Vector2i::lengthSquare() const {
    return (x * x) + (y * y);
}

size_t Vector2i::length() const {
    return (size_t) std::sqrt(lengthSquare());
}

[[maybe_unused]] void Vector2i::normalize() {
    size_t len = length();
    if (len == 0) {
        return;
    }
    x /= (int) len;
    y /= (int) len;
}

void Vector2i::ensureNotGreater(int max) {
    ::ensureNotGreater(x, max);
    ::ensureNotGreater(y, max);
}
