//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYDESTROYCONSUMER_H
#define R_TYPE_SERVER_ENTITYDESTROYCONSUMER_H


#include "Engine/Network/Packets/EntityDestroyPacket.h"
#include "Engine/Engine.h"
#include "Engine/Network/Packets/PacketConsumer.h"

class EntityDestroyConsumer : public PacketConsumer<EntityDestroyPacket, Engine&>{

    void consume(EntityDestroyPacket &packet, Engine &e) override;
};


#endif //R_TYPE_SERVER_ENTITYDESTROYCONSUMER_H
