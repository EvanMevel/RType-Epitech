//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H


#include <memory>
#include "Scene.h"
#include "Graphic/IGraphicLib.h"

#define ENGINE_TPS 60

/**
 * @brief base of the Engine that contains the current scene and the graphic library if it is set
 */
class Engine {
private:
    std::shared_ptr<Scene> current;
    EntityManager entityManager;
    std::unordered_map<std::type_index, std::any> engineComponents;
public:
    explicit Engine();

    explicit Engine(size_t startId);

    virtual ~Engine();

    template<class Module, class ...Args>
    std::shared_ptr<Module> registerModule(Args&&... args) {
        std::shared_ptr<Module> engineComponent = std::make_shared<Module>(args...);
        engineComponents[std::type_index(typeid(Module))] = engineComponent;
        return engineComponent;
    }
    template<class IModule, class Module, class ...Args>
    std::shared_ptr<IModule> registerIModule(Args&&... args) {
        std::shared_ptr<IModule> engineComponent = std::make_shared<Module>(args...);
        engineComponents[std::type_index(typeid(IModule))] = engineComponent;
        return engineComponent;
    }
    template<class Module>
    std::shared_ptr<Module> getModule() {
        return std::any_cast<std::shared_ptr<Module>>(engineComponents[std::type_index(typeid(Module))]);
    }

    template <class SceneType, class ...Args>
    std::shared_ptr<SceneType> createScene(Args&&... args) {
        return std::make_shared<SceneType>(entityManager, args...);
    }
    void setScene(std::shared_ptr<Scene> &scene);
    std::shared_ptr<Scene> &getScene();

    void updateScene(EnginePtr engine);

};

using EnginePtr = std::unique_ptr<Engine>&;

#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENGINE_H
