//
// Created by evans on 01/02/2023.
//

#ifndef R_TYPE_SERVER_ENEMYSHOOTSYSTEM_H
#define R_TYPE_SERVER_ENEMYSHOOTSYSTEM_H


#include "Engine/ISystem.h"

class EnemyShootSystem : public ISystem {
public:
    void update(std::unique_ptr<Engine> &engine) override;

};


#endif //R_TYPE_SERVER_ENEMYSHOOTSYSTEM_H
