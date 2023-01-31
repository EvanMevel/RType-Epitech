//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERMOVECONSUMER_H
#define R_TYPE_SERVER_PLAYERMOVECONSUMER_H


#include "RTypeServer.h"
#include "Engine/Network/Packets/PlayerMovePacket.h"

class PlayerMoveConsumer : public RTypePlayerPacketConsumer<PlayerMovePacket> {
public:
    explicit PlayerMoveConsumer(Engine &e);

    void consume(PlayerMovePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data,
                 std::shared_ptr<Entity> player) override;
};


#endif //R_TYPE_SERVER_PLAYERMOVECONSUMER_H
