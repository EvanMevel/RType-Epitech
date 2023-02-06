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

#include "PlayerShootSystem.h"
#include "Engine/Network/Packets/PlayerShootPacket.h"
#include "SoundManager.h"

PlayerShootSystem::PlayerShootSystem(const std::shared_ptr<Player> &player) : player(player){

}

void PlayerShootSystem::update(EnginePtr engine) {
    if (cooldown > 0) {
        cooldown--;
    }
    if (player->shoot && cooldown == 0) {
        engine->getModule<ClientNetServer>()->sendPacket(PlayerShootPacket(player->entity->getId()));
        cooldown = ENGINE_TPS / 2;
        auto lib = engine->getModule<IGraphicLib>();
        auto soundManager = engine->getModule<SoundManager>();
        auto projetcileSound = soundManager->getSound(SoundType::PROJECTILE);
        std::function<void(std::shared_ptr<IGraphicLib> lib, std::shared_ptr<ISound> projectileSound)> playSoundFunct = [](std::shared_ptr<IGraphicLib> lib, std::shared_ptr<ISound> projectileSound){
            lib->playSound(projectileSound);
        };
        lib->execOnLibThread(playSoundFunct, lib ,projetcileSound);
    }
}
