//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H


#include "Scene.h"

class Engine {
private:
    std::vector<Scene> scenes;
    Scene& scene;
    size_t nextId = 0;
public:
    explicit Engine(Scene &scene);
    void registerScene(Scene&);
    void setScene(Scene&);
    Scene &getScene() const;
    Entity createEntity();
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H
