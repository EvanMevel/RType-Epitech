//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_PINGPACKETCONSUMER_H
#define R_TYPE_SERVER_PINGPACKETCONSUMER_H

#include "Client/ClientNetServer.h"
#include "Engine/Network/Packets/PingPacket.h"

class PingPacketConsumer : public ClientPacketConsumer<PingPacket> {
public:
    void consume(PingPacket &packet, EnginePtr engine, RTypeServer server) override;
};


#endif //R_TYPE_SERVER_PINGPACKETCONSUMER_H
