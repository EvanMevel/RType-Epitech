//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_HANDSHAKERESPONSECONSUMER_H
#define R_TYPE_SERVER_HANDSHAKERESPONSECONSUMER_H

#include "Engine/Network/Packets/HandshakeResponsePacket.h"
#include "Engine/Engine.h"
#include "Engine/Network/Packets/PacketConsumer.h"
#include "Engine/Network/NetworkRemoteServer.h"

class HandshakeResponseConsumer : public PacketConsumer<HandshakeResponsePacket, Engine&> {
private:
    NetworkRemoteServer<Engine&> &server;
public:
    explicit HandshakeResponseConsumer(NetworkRemoteServer<Engine &> &server);

    void consume(HandshakeResponsePacket &packet, Engine &e) override;
};


#endif //R_TYPE_SERVER_HANDSHAKERESPONSECONSUMER_H
