//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERSHOOTCONSUMER_H
#define R_TYPE_SERVER_PLAYERSHOOTCONSUMER_H


#include "RTypeServer.h"
#include "Engine/Network/Packets/PlayerShootPacket.h"
#include "Engine/Engine.h"

class PlayerShootConsumer : public PacketClientConsumer<PlayerShootPacket, std::shared_ptr<ClientData>> {
private:
    Engine &e;
    RTypeServerPtr server;

public:
    PlayerShootConsumer(Engine &e, const RTypeServerPtr &server);

    void consume(PlayerShootPacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) override;
};


#endif //R_TYPE_SERVER_PLAYERSHOOTCONSUMER_H
