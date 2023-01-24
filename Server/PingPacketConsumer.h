//
// Created by evans on 24/01/2023.
//

#ifndef R_TYPE_SERVER_PINGPACKETCONSUMER_H
#define R_TYPE_SERVER_PINGPACKETCONSUMER_H

#include "RTypeServer.h"

class PingPacketConsumer : public PacketClientConsumer<PingPacket, ClientData&> {
public:
    PingPacketConsumer();

    void consume(PingPacket &packet, std::shared_ptr<NetClient> client, ClientData &data) override;
};


#endif //R_TYPE_SERVER_PINGPACKETCONSUMER_H
