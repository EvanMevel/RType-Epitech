//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERMOVECONSUMER_H
#define R_TYPE_SERVER_PLAYERMOVECONSUMER_H


#include "RTypeServer.h"
#include "Engine/Network/Packets/PlayerMovePacket.h"
#include "Engine/Engine.h"

class PlayerMoveConsumer : public PacketClientConsumer<PlayerMovePacket, std::shared_ptr<ClientData>> {
private:
    Engine &e;
    RTypeServerPtr server;

public:
    PlayerMoveConsumer(Engine &e, RTypeServerPtr server);

    void consume(PlayerMovePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) override;
};


#endif //R_TYPE_SERVER_PLAYERMOVECONSUMER_H
