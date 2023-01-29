//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_HANDSHAKECONSUMER_H
#define R_TYPE_SERVER_HANDSHAKECONSUMER_H

#include "RTypeServer.h"
#include "Engine/Engine.h"
#include "Engine/Network/Packets/HandshakePacket.h"
#include "Engine/Network/Packets/HandshakeResponsePacket.h"

class HandshakeConsumer : public PacketClientConsumer<HandshakePacket, std::shared_ptr<ClientData>> {
private:
    RTypeServerPtr server;
    Engine &e;
public:
    explicit HandshakeConsumer(RTypeServerPtr server, Engine &e);

    void consume(HandshakePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) override;
};


#endif //R_TYPE_SERVER_HANDSHAKECONSUMER_H
