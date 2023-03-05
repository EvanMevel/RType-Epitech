//
// Created by aaama on 03/03/2023.
//

#ifndef PONG_BOSSCREATOR_H
#define PONG_BOSSCREATOR_H


#include "Entity.h"
#include "Engine/Graphic/IGraphicLib.h"
#include "Engine.h"

/**
 * @brief BossCreator is an abstract class that will be used to create a boss
 */
class BossCreator {
public:
    virtual void createBoss(EnginePtr engine, std::shared_ptr<Entity> entity);
};


#endif //PONG_BOSSCREATOR_H
