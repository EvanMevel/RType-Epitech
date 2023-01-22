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