//
// Created by gugue on 04/03/2023.
//

#ifndef PONG_STARTGAMECONSUMER_H
#define PONG_STARTGAMECONSUMER_H


#include "Engine/Engine.h"
#include "Engine/Network/Packets/HandshakePacket.h"
#include "Engine/Network/NetServer.h"
#include "Server/ClientData.h"
#include "Server/RTypeServer.h"
#include "Engine/Network/Packets/StartGamePacket.h"


class StartGameConsumer: public RTypePacketConsumer<StartGamePacket> {
public:
    static bool gameStarted;

    explicit StartGameConsumer(EnginePtr e);

    void consume(StartGamePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) override;
};


#endif //PONG_STARTGAMECONSUMER_H
