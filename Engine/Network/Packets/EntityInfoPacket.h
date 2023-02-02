//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_ENTITYINFOPACKET_H
#define R_TYPE_SERVER_ENTITYINFOPACKET_H


#include "IPacket.h"
#include <memory>
#include "Engine/Entity.h"
#include "Engine/EntityType.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Component/PositionComponent.h"

class EntityInfoPacket : public IPacket {
public:
    static const int ID = 7;
    size_t id;
    EntityType type;
    int x;
    int y;

    EntityInfoPacket();

    EntityInfoPacket(size_t id, EntityType type, int x, int y);

    explicit EntityInfoPacket(std::shared_ptr<Entity> entity);

    EntityInfoPacket(std::shared_ptr<Entity> entity, EntityType type, std::shared_ptr<PositionComponent> pos);

    EntityInfoPacket(std::shared_ptr<Entity> entity, std::shared_ptr<EntityTypeComponent> type, std::shared_ptr<PositionComponent> pos);

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_ENTITYINFOPACKET_H
