//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERSHOOTCONSUMER_H
#define R_TYPE_SERVER_PLAYERSHOOTCONSUMER_H


#include "RTypeServer.h"
#include "Engine/Network/Packets/PlayerShootPacket.h"

class PlayerShootConsumer : public RTypePlayerPacketConsumer<PlayerShootPacket> {
public:
    explicit PlayerShootConsumer(Engine &e);

    void consume(PlayerShootPacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data,
                 std::shared_ptr<Entity> player) override;
};


#endif //R_TYPE_SERVER_PLAYERSHOOTCONSUMER_H
