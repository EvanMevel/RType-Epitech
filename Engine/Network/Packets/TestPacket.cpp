//
// Created by evans on 21/01/2023.
//

#include "TestPacket.h"

void TestPacket::read(ByteArray &buffer) {
    buffer.read(_value);
}

void TestPacket::write(ByteArray &buffer) const {
    buffer.write(_value);
}

void TestPacket::setValue(int value) {
    _value = value;
}

int TestPacket::getValue() const {
    return _value;
}
