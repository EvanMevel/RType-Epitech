//
// Created by evans on 18/01/2023.
//

#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <cstddef>

class Vector2f {
public:
    float x, y;

    Vector2f operator+(const Vector2f& v2) const;
    Vector2f operator-(const Vector2f& v2) const;
    Vector2f operator*(const Vector2f& v2) const;
    Vector2f& operator=(const Vector2f& v2);
};

#endif
