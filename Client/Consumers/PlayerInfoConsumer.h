//
// Created by evans on 27/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERINFOCONSUMER_H
#define R_TYPE_SERVER_PLAYERINFOCONSUMER_H


#include "Client/ClientNetServer.h"
#include "Engine/Network/Packets/PlayerInfoPacket.h"

class PlayerInfoConsumer : public ClientPacketConsumer<PlayerInfoPacket> {
private:
    std::shared_ptr<ITexture> playerTexture;
public:
    PlayerInfoConsumer(std::shared_ptr<ITexture> playerTexture);

    void consume(PlayerInfoPacket &packet, EnginePtr engine, RTypeServer server) override;
};


#endif //R_TYPE_SERVER_PLAYERINFOCONSUMER_H
