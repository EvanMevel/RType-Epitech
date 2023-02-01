//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYINFOCONSUMER_H
#define R_TYPE_SERVER_ENTITYINFOCONSUMER_H


#include "Client/ClientNetServer.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"

class EntityInfoConsumer : public ClientPacketConsumer<EntityInfoPacket> {
private:
    std::unordered_map<EntityType, std::shared_ptr<ITexture>> textures;
public:
    explicit EntityInfoConsumer(const std::unordered_map<EntityType, std::shared_ptr<ITexture>> &textures);

    void consume(EntityInfoPacket &packet, EnginePtr engine, RTypeServer server) override;
};


#endif //R_TYPE_SERVER_ENTITYINFOCONSUMER_H
