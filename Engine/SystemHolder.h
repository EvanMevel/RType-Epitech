// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

    /**
     * @brief Add a system to the holder
     * @param system
     */
    void addSystem(std::shared_ptr<ISystem> system) {
        this->systems.push_back(system);
    }
};

#endif //R_TYPE_SERVER_SYSTEMHOLDER_H
