//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERMOVESYSTEM_H
#define R_TYPE_SERVER_PLAYERMOVESYSTEM_H

#include "Player.h"
#include "Engine/Engine.h"
#include "Engine/ISystem.h"
#include "ClientNetServer.h"

class PlayerMoveSystem : public ISystem {
private:
    std::shared_ptr<Player> player;
public:
    PlayerMoveSystem(const std::shared_ptr<Player> &player);

    void update(Engine &engine) override;
};


#endif //R_TYPE_SERVER_PLAYERMOVESYSTEM_H
