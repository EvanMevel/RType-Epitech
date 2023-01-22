//
// Created by evans on 21/01/2023.
//

#ifndef R_TYPE_SERVER_TESTPACKET_H
#define R_TYPE_SERVER_TESTPACKET_H


#include "IPacket.h"

class TestPacket : public IPacket {
private:
    int _value = 0;
public:
    static const int ID = 1;
    TestPacket() = default;
    ~TestPacket() = default;

    void setValue(int value);
    int getValue() const;

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_TESTPACKET_H
