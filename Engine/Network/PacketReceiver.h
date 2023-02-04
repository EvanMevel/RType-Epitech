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

#ifndef R_TYPE_SERVER_PACKETRECEIVER_H
#define R_TYPE_SERVER_PACKETRECEIVER_H

#include "Engine/Network/Packets/PacketSerializer.h"

class PacketReceiver {
private:
    const PacketSerializer packetSerializer;
protected:
    const unsigned char _magic = 232;
public:
    PacketReceiver() = default;
    virtual ~PacketReceiver() = default;

    template<class Packet>
    void sendPacket(const Packet &packet) {
        ByteArray arr;
        arr.write(_magic);
        packetSerializer.serialize(packet, arr);
        std::string str = arr.getString();
        send(str.c_str(), str.length());
    }

    virtual void send(const char *message, int length) = 0;

};

#endif //R_TYPE_SERVER_PACKETRECEIVER_H
