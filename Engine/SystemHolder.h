//
// Created by evans on 22/01/2023.
//

#ifndef R_TYPE_SERVER_SYSTEMHOLDER_H
#define R_TYPE_SERVER_SYSTEMHOLDER_H

#include <memory>
#include <vector>
#include "ISystem.h"

class SystemHolder {
protected:
    std::vector<std::shared_ptr<ISystem>> systems;
public:
    SystemHolder() {}
    SystemHolder(const SystemHolder &other) {
        for (const auto &sys: other.systems) {
            systems.push_back(sys);
        }
    }

    template <class System, class ...Args>
    void addSystem(Args&&... args) {
        this->systems.push_back(std::make_shared<System>(args...));
    }

    void update(Engine &engine) {
        for (const auto &sys: systems) {
            sys->update(engine);
        }
    }
};

#endif //R_TYPE_SERVER_SYSTEMHOLDER_H
