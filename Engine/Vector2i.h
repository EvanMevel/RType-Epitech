//
// Created by gugue on 24/01/2023.
//

#ifndef R_TYPE_SERVER_VECTOR2I_H
#define R_TYPE_SERVER_VECTOR2I_H

#include <cmath>

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
