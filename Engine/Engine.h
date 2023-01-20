//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H


#include "Scene.h"
#include "Graphic/IGraphicLib.h"

class Engine {
private:
    std::vector<Scene*> scenes;
    Scene* _scene;
    EntityManager entityManager;
    IGraphicLib* _graphicLib;
public:
    explicit Engine();

    virtual ~Engine();

    Scene *createScene();
    void setScene(Scene*);
    Scene *getScene() const;

    void setGraphicLib(IGraphicLib *graphicLib);

    IGraphicLib *getGraphicLib() const;

    void updateScene();

    void updateGraphicLib();
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H
