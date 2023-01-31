//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYINFOCONSUMER_H
#define R_TYPE_SERVER_ENTITYINFOCONSUMER_H


#include "Engine/Network/Packets/EntityInfoPacket.h"
#include "Engine/Engine.h"
#include "Engine/Network/Packets/PacketConsumer.h"
#include "Engine/EntityType.h"

class EntityInfoConsumer : public PacketConsumer<EntityInfoPacket, Engine&> {
private:
    std::unordered_map<EntityType, std::shared_ptr<ITexture>> textures;
public:
    explicit EntityInfoConsumer(const std::unordered_map<EntityType, std::shared_ptr<ITexture>> &textures);

    void consume(EntityInfoPacket &packet, Engine &e) override;
};


#endif //R_TYPE_SERVER_ENTITYINFOCONSUMER_H
