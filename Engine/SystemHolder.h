//
// Created by evans on 22/01/2023.
//

#ifndef R_TYPE_SERVER_SYSTEMHOLDER_H
#define R_TYPE_SERVER_SYSTEMHOLDER_H

#include <iostream>
#include <memory>
#include <vector>
#include "ISystem.h"

/**
 * @brief Holds systems
 * Systems can be added using the addSystem method
 */
class SystemHolder : public ISystem {
protected:
    std::vector<std::shared_ptr<ISystem>> systems;
public:
    SystemHolder() {}
    SystemHolder(const SystemHolder &other) {
        for (const auto &sys: other.systems) {
            systems.push_back(sys);
        }
    }

    /**
     * @brief Add a system to the holder
     * @tparam System
     * @tparam Args
     * @param args
     */
    template <class System, class ...Args>
    void addSystem(Args&&... args) {
        this->systems.push_back(std::make_shared<System>(args...));
    }

    /**
     * @brief Call the update method of all systems
     * @param engine
     */
    void update(EnginePtr engine) override {
        for (const auto &sys: systems) {
            sys->update(engine);
        }
    }
};

#endif //R_TYPE_SERVER_SYSTEMHOLDER_H
