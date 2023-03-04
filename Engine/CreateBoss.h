//
// Created by aaama on 03/03/2023.
//

#ifndef PONG_CREATEBOSS_H
#define PONG_CREATEBOSS_H


#include "Entity.h"
#include "Engine/Graphic/IGraphicLib.h"
#include "Engine.h"

class BossCreator{
private:
    int health;
public:
    virtual void createBoss(EnginePtr engine, std::shared_ptr<Entity> entity);
};


#endif //PONG_CREATEBOSS_H
