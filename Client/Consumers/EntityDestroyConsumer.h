//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYDESTROYCONSUMER_H
#define R_TYPE_SERVER_ENTITYDESTROYCONSUMER_H


#include "Client/ClientNetServer.h"
#include "Engine/Network/Packets/EntityDestroyPacket.h"

class EntityDestroyConsumer : public ClientPacketConsumer<EntityDestroyPacket>{
public:
    void consume(EntityDestroyPacket &packet, EnginePtr engine, RTypeServer server) override;
};

#endif //R_TYPE_SERVER_ENTITYDESTROYCONSUMER_H
