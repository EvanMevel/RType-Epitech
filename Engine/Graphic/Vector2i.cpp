//
// Created by evans on 18/01/2023.
//

#include "Vector2i.h"

Vector2i Vector2i::operator+(const Vector2i& v2) const {
    return Vector2i{x + v2.x, y + v2.y};
}

Vector2i Vector2i::operator-(const Vector2i& v2) const {
    return Vector2i{x - v2.x, y - v2.y};
}

Vector2i Vector2i::operator*(const Vector2i& v2) const {
    return Vector2i{x * v2.x, y * v2.y};
}

Vector2i& Vector2i::operator=(const Vector2i& v2) {
    x = v2.x;
    y = v2.y;
    return *this;
}