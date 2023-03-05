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

#include "PacketSwitchWeaponConsumer.h"
#include "Engine/Engine.h"
#include "Client/Player/Player.h"
#include "Engine/Component/WeaponComponent.h"
#include "Engine/engineLua/LuaWeaponFactory.h"

void PacketSwitchWeaponConsumer::consume(PacketSwitchWeapon &packet, EnginePtr engine, RTypeServer server) {
    auto player = engine->getModule<Player>();
    if (!player || player->entity->getId() != packet.getId()) {
        return;
    }
    auto weaponFactory = engine->getModule<LuaWeaponFactoryBase>();
    auto weaponComponent = player->entity->getComponent<WeaponComponent>();

    if (!weaponComponent || !weaponFactory) {
        return;
    }
    auto weapon = weaponFactory->getWeapon(packet.getWeaponName());
    if (!weapon) {
        return;
    }
    weaponComponent->setWeapon(weapon);
    std::cout << "Weapon switched to " << packet.getWeaponName() << std::endl;
}
