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

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ISYSTEM_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ISYSTEM_H

#include <string>
#include <memory>

class Engine;

using EnginePtr = std::unique_ptr<Engine>&;

/**
 * @brief ISystem is the base class for all systems of the ECS
 * @details override the update method to define the behavior of the system
 */
class ISystem {
public:
    ISystem();
    ~ISystem();

    /**
     * @brief update is what will be called by the engine to use the system
     * @details override this method to define the behavior of the system
     * @param engine the engine that is calling the system
     */
    virtual void update(EnginePtr engine) = 0;

    virtual std::string getName();
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ISYSTEM_H
