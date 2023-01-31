//
// Created by evans on 27/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERINFOPACKET_H
#define R_TYPE_SERVER_PLAYERINFOPACKET_H


#include "IPacket.h"
#include <memory>
#include "Engine/Entity.h"
#include "Engine/Component/PositionComponent.h"

class PlayerInfoPacket : public IPacket {

public:
    static const int ID = 5;
    PlayerInfoPacket();

    size_t playerId;
    int x;
    int y;

    explicit PlayerInfoPacket(std::shared_ptr<Entity> entity);

    PlayerInfoPacket(std::shared_ptr<Entity> entity, std::shared_ptr<PositionComponent> pos);

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_PLAYERINFOPACKET_H
