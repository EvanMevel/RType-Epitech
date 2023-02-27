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

#ifndef R_TYPE_SERVER_COLLIDERHITBOXSYSTEM_H
#define R_TYPE_SERVER_COLLIDERHITBOXSYSTEM_H

#include <functional>
#include "Engine/ISystem.h"
#include "Engine/Entity.h"

/**
 * @brief System that checks if a collider is colliding with another entity
 */
class ColliderHitboxSystem : public ISystem {
private:
    std::function<void(EnginePtr engine, std::shared_ptr<Entity> touched, int damages)> _onDamage;
public:
    void update(EnginePtr engine) override;

    ColliderHitboxSystem(std::function<void(EnginePtr engine, std::shared_ptr<Entity> touched, int damages)>);
    std::string getName() override;
};


#endif //R_TYPE_SERVER_COLLIDERHITBOXSYSTEM_H
