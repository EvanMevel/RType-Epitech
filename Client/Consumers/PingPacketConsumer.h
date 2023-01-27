//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_PINGPACKETCONSUMER_H
#define R_TYPE_SERVER_PINGPACKETCONSUMER_H


#include "Engine/Network/Packets/PingPacket.h"
#include "Engine/Engine.h"
#include "Engine/Network/Packets/PacketConsumer.h"
#include "Engine/Network/NetworkRemoteServer.h"

class PingPacketConsumer : public PacketConsumer<PingPacket, Engine&> {
private:
    NetworkRemoteServer<Engine&> &server;
public:
    explicit PingPacketConsumer(NetworkRemoteServer<Engine &> &server);

public:
    void consume(PingPacket &packet, Engine &e) override;
};


#endif //R_TYPE_SERVER_PINGPACKETCONSUMER_H
