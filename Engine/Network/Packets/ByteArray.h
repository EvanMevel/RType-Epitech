//
// Created by evans on 21/01/2023.
//

#ifndef R_TYPE_SERVER_BYTEARRAY_H
#define R_TYPE_SERVER_BYTEARRAY_H

#include <sstream>

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

    std::string getString() const {
        return _buffer.str();
    }
};

ByteArray& operator<<(ByteArray &buffer, const std::string &value);

ByteArray& operator<<(ByteArray &buffer, const int &value);

ByteArray& operator>>(ByteArray &buffer, int &value);


#endif //R_TYPE_SERVER_BYTEARRAY_H
