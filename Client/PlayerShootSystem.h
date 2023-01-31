//
// Created by evans on 31/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERSHOOTSYSTEM_H
#define R_TYPE_SERVER_PLAYERSHOOTSYSTEM_H


#include "Player.h"
#include "Engine/Engine.h"
#include "Engine/ISystem.h"
#include "ClientNetServer.h"

class PlayerShootSystem : public ISystem {
private:
    std::shared_ptr<Player> player;
    size_t cooldown = 0;
public:
    PlayerShootSystem(const std::shared_ptr<Player> &player);

    void update(Engine &engine) override;
};


#endif //R_TYPE_SERVER_PLAYERSHOOTSYSTEM_H
