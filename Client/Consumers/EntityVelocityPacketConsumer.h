//
// Created by evans on 01/02/2023.
//

#ifndef R_TYPE_SERVER_ENTITYVELOCITYPACKETCONSUMER_H
#define R_TYPE_SERVER_ENTITYVELOCITYPACKETCONSUMER_H


#include "Engine/Network/Packets/PacketConsumer.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Engine/Engine.h"

class EntityVelocityPacketConsumer : public PacketConsumer<EntityVelocityPacket, Engine&>{
public:
    void consume(EntityVelocityPacket &packet, Engine& e) override;
};


#endif //R_TYPE_SERVER_ENTITYVELOCITYPACKETCONSUMER_H
