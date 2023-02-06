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

#ifndef R_TYPE_SERVER_VECTOR2I_H
#define R_TYPE_SERVER_VECTOR2I_H

#include <cmath>

/**
 * @brief A 2D vector
 */
class Vector2i {
private:
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

public:
    int x;
    int y;

    Vector2i(int x = 0, int y = 0) : x(x), y(y) {}

    int getX() const {
        return x;
    }

    void setX(int x) {
        Vector2i::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        Vector2i::y = y;
    }

    void operator+=(const Vector2i &other) {
        x += other.x;
        y += other.y;
    }

    void decrementTo0(size_t decr) {
        absoluteVarTo0(x, decr);
        absoluteVarTo0(y, decr);
    }

    Vector2i clone() const {
        return {x, y};
    }

    size_t lengthSquare() const {
        return x * x + y * y;
    }

    size_t length() const {
        return (size_t) std::sqrt(lengthSquare());
    }

    void normalize() {
        size_t len = length();
        if (len == 0) {
            return;
        }
        x /= (int) len;
        y /= (int) len;
    }

    void ensureNotGreater(int max) {
        ensureNotGreater(x, max);
        ensureNotGreater(y, max);
    }
};


#endif //R_TYPE_SERVER_VECTOR2I_H
