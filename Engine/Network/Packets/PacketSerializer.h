//
// Created by evans on 21/01/2023.
//

#ifndef R_TYPE_SERVER_PACKETSERIALIZER_H
#define R_TYPE_SERVER_PACKETSERIALIZER_H


#include <unordered_map>
#include <any>
#include "ByteArray.h"

/**
 * @brief Serialize a packet to a ByteArray, writing its id and then its content
 */
class PacketSerializer {
public:
    PacketSerializer() = default;
    ~PacketSerializer() = default;

    template<class Packet>
    void serialize(const Packet &packet, ByteArray &buffer) const {
        int id = packet.ID;
        buffer.write(id);
        packet.write(buffer);
    }

    template<class Packet>
    void deserialize(Packet &packet, ByteArray &buffer) const {
        packet.read(buffer);
    }
};


#endif //R_TYPE_SERVER_PACKETSERIALIZER_H
