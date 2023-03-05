//
// Created by aaama on 05/03/2023.
//

#ifndef PONG_SCORECONSUMER_H
#define PONG_SCORECONSUMER_H


#include "Engine/Network/Packets/ScorePacket.h"
#include "Client/ClientNetServer.h"

class ScoreConsumer : public ClientPacketConsumer<ScorePacket> {
public:
    void consume(ScorePacket &packet, std::unique_ptr<Engine> &engine, RTypeServer server) override;
};


#endif //PONG_SCORECONSUMER_H
