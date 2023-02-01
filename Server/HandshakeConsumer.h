//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_HANDSHAKECONSUMER_H
#define R_TYPE_SERVER_HANDSHAKECONSUMER_H

#include "RTypeServer.h"
#include "Engine/Network/Packets/HandshakePacket.h"

class HandshakeConsumer : public RTypePacketConsumer<HandshakePacket> {
public:
    explicit HandshakeConsumer(EnginePtr e);

    void consume(HandshakePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) override;
};


#endif //R_TYPE_SERVER_HANDSHAKECONSUMER_H
