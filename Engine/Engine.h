//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H


#include <memory>
#include "Scene.h"
#include "Graphic/IGraphicLib.h"

/**
 * @brief base of the Engine that contains the current scene and the graphic library if it is set
 */
class Engine {
private:
    std::shared_ptr<Scene> current;
    EntityManager entityManager;
    std::shared_ptr<IGraphicLib> _graphicLib;
public:
    explicit Engine();

    virtual ~Engine();

    template <class SceneType, class ...Args>
    std::shared_ptr<SceneType> createScene(Args&&... args) {
        return std::make_shared<SceneType>(entityManager, args...);
    }
    void setScene(std::shared_ptr<Scene> &scene);
    std::shared_ptr<Scene> &getScene();

    void setGraphicLib(std::shared_ptr<IGraphicLib> &graphicLib);

    std::shared_ptr<IGraphicLib> &getGraphicLib();

    void updateScene();

    void updateGraphicLib();
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H
