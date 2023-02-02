//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_PINGPACKETCONSUMER_H
#define R_TYPE_SERVER_PINGPACKETCONSUMER_H

#include "RTypeServer.h"
#include "Engine/Network/Packets/PingPacket.h"

class PingPacketConsumer : public PacketClientConsumer<PingPacket, std::shared_ptr<ClientData>> {
public:
    PingPacketConsumer();

    void consume(PingPacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) override;
};


#endif //R_TYPE_SERVER_PINGPACKETCONSUMER_H
