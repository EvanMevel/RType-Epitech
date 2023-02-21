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

#include "ByteArray.h"


ByteArray& operator<<(ByteArray &buffer, const std::string &value) {
    unsigned int size = (unsigned int) value.length();
    buffer.write(size);
    buffer.write(value.c_str(), value.length());
    return buffer;
}

ByteArray& operator>>(ByteArray &buffer, std::string &value) {
    unsigned int size = 0;
    buffer.read(size);
    char buff[size + 1];
    buffer.read(buff, size);
    buff[size] = '\0';
    value = buff;
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

ByteArray& operator<<(ByteArray &buffer, const unsigned int &value) {
    buffer.write(value);
    return buffer;
}

ByteArray& operator>>(ByteArray &buffer, unsigned int &value) {
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