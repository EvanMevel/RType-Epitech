//
// Created by gugue on 04/03/2023.
//

#ifndef PONG_STARTGAMECONSUMER_H
#define PONG_STARTGAMECONSUMER_H


#include "Engine/Network/Packets/StartGamePacket.h"
#include "Client/ClientNetServer.h"

class StartGameConsumer: public ClientPacketConsumer<StartGamePacket> {
public:
    void consume(StartGamePacket &packet, std::unique_ptr<Engine> &engine, RTypeServer server) override;
};


#endif //PONG_STARTGAMECONSUMER_H
