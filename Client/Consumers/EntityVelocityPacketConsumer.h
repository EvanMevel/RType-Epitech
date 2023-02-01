//
// Created by evans on 01/02/2023.
//

#ifndef R_TYPE_SERVER_ENTITYVELOCITYPACKETCONSUMER_H
#define R_TYPE_SERVER_ENTITYVELOCITYPACKETCONSUMER_H


#include "Client/ClientNetServer.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"

class EntityVelocityPacketConsumer : public ClientPacketConsumer<EntityVelocityPacket>{
public:
    void consume(EntityVelocityPacket &packet, EnginePtr engine, RTypeServer server) override;
};


#endif //R_TYPE_SERVER_ENTITYVELOCITYPACKETCONSUMER_H
