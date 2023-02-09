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

#ifndef R_TYPE_SERVER_PLAYERSHOOTSYSTEM_H
#define R_TYPE_SERVER_PLAYERSHOOTSYSTEM_H


#include "Player.h"
#include "Engine/Engine.h"
#include "Engine/ISystem.h"
#include "Client/ClientNetServer.h"

/**
 * @brief System that handles the shooting of the player
 */
class PlayerShootSystem : public ISystem {
private:
    std::shared_ptr<Player> player;
    size_t cooldown = 0;
public:
    PlayerShootSystem(const std::shared_ptr<Player> &player);

    void update(EnginePtr engine) override;
};


#endif //R_TYPE_SERVER_PLAYERSHOOTSYSTEM_H
