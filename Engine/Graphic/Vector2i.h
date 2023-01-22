//
// Created by evans on 18/01/2023.
//

#ifndef VECTOR2I_H
#define VECTOR2I_H

#include <cstddef>

class Vector2i {
public:
    int x, y;

    Vector2i operator+(const Vector2i& v2) const;
    Vector2i operator-(const Vector2i& v2) const;
    Vector2i operator*(const Vector2i& v2) const;
    Vector2i& operator=(const Vector2i& v2);
};

#endif
