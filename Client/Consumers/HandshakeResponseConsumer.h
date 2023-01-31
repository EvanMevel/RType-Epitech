//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_HANDSHAKERESPONSECONSUMER_H
#define R_TYPE_SERVER_HANDSHAKERESPONSECONSUMER_H

#include "Client/ClientNetServer.h"
#include "Engine/Network/Packets/HandshakeResponsePacket.h"

class HandshakeResponseConsumer : public ClientPacketConsumer<HandshakeResponsePacket> {
public:
    void consume(HandshakeResponsePacket &packet, Engine &e) override;
};


#endif //R_TYPE_SERVER_HANDSHAKERESPONSECONSUMER_H
