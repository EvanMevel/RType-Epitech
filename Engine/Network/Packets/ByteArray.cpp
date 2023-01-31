//
// Created by evans on 21/01/2023.
//

#include "ByteArray.h"


ByteArray& operator<<(ByteArray &buffer, const std::string &value) {
    buffer.write(value.c_str(), value.length());
    return buffer;
}

ByteArray& operator<<(ByteArray &buffer, const int &value) {
    buffer.write(value);
    return buffer;
}

ByteArray& operator>>(ByteArray &buffer, int &value) {
    buffer.read(value);
    return buffer;
}

ByteArray& operator<<(ByteArray &buffer, const long long &value) {
    buffer.write(value);
    return buffer;
}

ByteArray& operator>>(ByteArray &buffer, long long &value) {
    buffer.read(value);
    return buffer;
}

ByteArray& operator<<(ByteArray &buffer, const unsigned long long &value) {
    buffer.write(value);
    return buffer;
}

ByteArray& operator>>(ByteArray &buffer, unsigned long long &value) {
    buffer.read(value);
    return buffer;
}

ByteArray& operator<<(ByteArray &buffer, const Vector2i &value) {
    buffer.write(value.x);
    buffer.write(value.y);
    return buffer;
}

ByteArray& operator>>(ByteArray &buffer, Vector2i &value) {
    buffer.read(value.x);
    buffer.read(value.y);
    return buffer;
}