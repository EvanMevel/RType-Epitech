//
// Created by evans on 28/01/2023.
//

#ifndef R_TYPE_SERVER_PLAYERKEYSSYSTEM_H
#define R_TYPE_SERVER_PLAYERKEYSSYSTEM_H

#include "Engine/ISystem.h"
#include "ClientNetServer.h"
#include "Player.h"

class PlayerKeysSystem : public ISystem {
private:
    std::shared_ptr<Player> player;
public:
    void update(EnginePtr engine) override;

    std::string getName() override;

    explicit PlayerKeysSystem(const std::shared_ptr<Player> &player);
};


#endif //R_TYPE_SERVER_PLAYERKEYSSYSTEM_H
