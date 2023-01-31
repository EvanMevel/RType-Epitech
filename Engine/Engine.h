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
    std::unordered_map<std::type_index, std::any> engineComponents;
    std::shared_ptr<IGraphicLib> _graphicLib;
    unsigned long long currentTick = 0;
public:
    explicit Engine();

    virtual ~Engine();

    template <class SceneType, class ...Args>
    std::shared_ptr<SceneType> createScene(Args&&... args) {
        return std::make_shared<SceneType>(entityManager, args...);
    }
    void setScene(std::shared_ptr<Scene> &scene);
    std::shared_ptr<Scene> &getScene();

    template<class EngineComponent, class ...Args>
    std::shared_ptr<EngineComponent> registerEngineComponent(Args&&... args) {
        std::shared_ptr<EngineComponent> engineComponent = std::make_shared<EngineComponent>(args...);
        engineComponents[std::type_index(typeid(EngineComponent))] = engineComponent;
        return engineComponent;
    }
    template<class IEngineComponent, class EngineComponent, class ...Args>
    std::shared_ptr<IEngineComponent> registerIEngineComponent(Args&&... args) {
        std::shared_ptr<IEngineComponent> engineComponent = std::make_shared<EngineComponent>(args...);
        engineComponents[std::type_index(typeid(IEngineComponent))] = engineComponent;
        return engineComponent;
    }

    template<class EngineComponent>
    std::shared_ptr<EngineComponent> getEngineComponent() {
        return std::any_cast<std::shared_ptr<EngineComponent>>(engineComponents[std::type_index(typeid(EngineComponent))]);
    }

    void updateScene();

    unsigned long long int getCurrentTick() const;

    void setCurrentTick(unsigned long long int currentTick);
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H
