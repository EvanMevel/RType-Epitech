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

#ifndef R_TYPE_SERVER_BYTEARRAY_H
#define R_TYPE_SERVER_BYTEARRAY_H

#include <sstream>
#include "Engine/Vector2i.h"
#include "Engine/EngineTypes.h"
#include "Engine/Scene.h"
/**
 * @brief ByteArray is a buffer of bytes that can be used to serialize and deserialize data
 */
class ByteArray {
private:
    std::stringbuf _buffer;
public:
    template<class Type>
    void write(const Type &value) {
        _buffer.sputn(reinterpret_cast<const char*>(&value), sizeof(Type));
    }

    void write(const char *value, int length) {
        _buffer.sputn(value, length);
    }

    template<class Type>
    void read(Type &value) {
        _buffer.sgetn(reinterpret_cast<char*>(&value), sizeof(Type));
    }

    void read(char *buff, unsigned int length) {
        _buffer.sgetn(buff, length);
    }

    std::string getString() const {
        return _buffer.str();
    }
};

ByteArray& operator<<(ByteArray &buffer, const std::string &value);

ByteArray& operator>>(ByteArray &buffer, std::string &value);

ByteArray& operator<<(ByteArray &buffer, const int &value);

ByteArray& operator>>(ByteArray &buffer, int &value);

ByteArray& operator<<(ByteArray &buffer, const unsigned int &value);

ByteArray& operator>>(ByteArray &buffer, unsigned int &value);

ByteArray& operator<<(ByteArray &buffer, const long long &value);

ByteArray& operator>>(ByteArray &buffer, long long &value);

ByteArray& operator<<(ByteArray &buffer, const unsigned long long &value);

ByteArray& operator>>(ByteArray &buffer, unsigned long long &value);

ByteArray& operator<<(ByteArray &buffer, const Vector2i &value);

ByteArray& operator>>(ByteArray &buffer, Vector2i &value);

ByteArray& operator<<(ByteArray &buffer, const std::shared_ptr<Scene>);

ByteArray& operator>>(ByteArray &buffer, std::shared_ptr<Scene>);

#endif //R_TYPE_SERVER_BYTEARRAY_H
