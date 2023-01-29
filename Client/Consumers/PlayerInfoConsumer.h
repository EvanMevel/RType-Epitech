//
// Created by evans on 27/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERINFOCONSUMER_H
#define R_TYPE_SERVER_PLAYERINFOCONSUMER_H


#include "Engine/Network/Packets/PlayerInfoPacket.h"
#include "Engine/Engine.h"
#include "Engine/Network/Packets/PacketConsumer.h"

class PlayerInfoConsumer : public PacketConsumer<PlayerInfoPacket, Engine&> {
private:
    ITexture playerTexture;
public:
    explicit PlayerInfoConsumer(ITexture playerTexture);

public:
    void consume(PlayerInfoPacket &packet, Engine &e) override;
};


#endif //R_TYPE_SERVER_PLAYERINFOCONSUMER_H
