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

#include "LevelSystem.h"
#include "Engine/Engine.h"
#include "RTypeServer.h"
#include "Engine/Component/IAComponent.h"
#include "Engine/Component/PhysicComponent.h"
#include "Engine/Component/InanimateComponent.h"
#include "Engine/Network/Packets/PacketWin.h"

LevelSystem::LevelSystem(std::shared_ptr<Level> level) : _level(level) {

}

void LevelSystem::update(std::unique_ptr<Engine> &engine) {
    if (finished)
        return;
    RTypeServerPtr server = engine->getModule<RTypeServer>();
    if (server->getClientCount() == 0)
        return;
    _x += 1;
    if (_level->update(_x, engine)) {
        finished = true;
        server->broadcast(PacketWin());
        return;
    }

    std::function<void(std::shared_ptr<Entity>)> moveEntity = [](std::shared_ptr<Entity> ent) {
        auto ia = ent->getComponent<IAComponent>();
        auto inanim = ent->getComponent<InanimateComponent>();
        auto phys = ent->getComponent<PhysicComponent>();
        if ((ia || inanim) && phys) {
            phys->velocity.x -= 1;
        }
    };
    engine->getScene()->forEachEntity(moveEntity);
}
