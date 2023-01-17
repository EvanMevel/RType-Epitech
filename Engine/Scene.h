//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H


#include <vector>
#include "Entity.h"
#include "ISystem.h"

class Engine;

class Scene {
    private:
        std::vector<Entity> entities;
        std::vector<ISystem> systems;
    public:
        void update(Engine);

};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_SCENE_H
