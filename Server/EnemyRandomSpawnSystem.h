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

#ifndef R_TYPE_SERVER_ENEMYRANDOMSPAWNSYSTEM_H
#define R_TYPE_SERVER_ENEMYRANDOMSPAWNSYSTEM_H

#include "Engine/ISystem.h"
#include <random>

/**
 * @brief System that spawns enemies randomly
 */
class EnemyRandomSpawnSystem : public ISystem {
private:
    size_t count = 0;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> distrx;
    std::uniform_int_distribution<> distry;;
    std::uniform_int_distribution<> distrType;
public:
    EnemyRandomSpawnSystem();

    void update(std::unique_ptr<Engine> &engine) override;
};


#endif //R_TYPE_SERVER_ENEMYRANDOMSPAWNSYSTEM_H
