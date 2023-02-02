//
// Created by evans on 01/02/2023.
//

#ifndef R_TYPE_SERVER_ENEMYRANDOMSPAWNSYSTEM_H
#define R_TYPE_SERVER_ENEMYRANDOMSPAWNSYSTEM_H

#include "Engine/ISystem.h"
#include <random>

class EnemyRandomSpawnSystem : public ISystem {
private:
    size_t count = 0;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> distr;
public:
    EnemyRandomSpawnSystem();

    void update(std::unique_ptr<Engine> &engine) override;
};


#endif //R_TYPE_SERVER_ENEMYRANDOMSPAWNSYSTEM_H
