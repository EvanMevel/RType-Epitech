//
// Created by evans on 21/01/2023.
//

#ifndef R_TYPE_SERVER_PACKETRECEIVER_H
#define R_TYPE_SERVER_PACKETRECEIVER_H

#include "Engine/Network/Packets/PacketSerializer.h"

class PacketReceiver {
private:
    const PacketSerializer packetSerializer;
protected:
    const unsigned char _magic = 242;
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
