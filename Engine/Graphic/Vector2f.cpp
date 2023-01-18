//
// Created by evans on 18/01/2023.
//

#include "Vector2f.h"

Vector2f Vector2f::operator+(const Vector2f& v2) const {
    return Vector2f{x + v2.x, y + v2.y};
}

Vector2f Vector2f::operator-(const Vector2f& v2) const {
    return Vector2f{x - v2.x, y - v2.y};
}

Vector2f Vector2f::operator*(const Vector2f& v2) const {
    return Vector2f{x * v2.x, y * v2.y};
}

Vector2f& Vector2f::operator=(const Vector2f& v2) {
    x = v2.x;
    y = v2.y;
    return *this;
}