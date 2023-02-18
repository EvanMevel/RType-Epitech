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

#include <iostream>
#include "PlayerInfoConsumer.h"
#include "Engine/EntityUtils.h"
#include "Client/Player/Player.h"
#include "Client/Player/PlayerKeysSystem.h"
#include "Client/Player/PlayerMoveSystem.h"
#include "Client/Player/PlayerShootSystem.h"
#include "Client/Sprites/SpriteComponent.h"
#include "Engine/engineLua/LuaEntityTypeFactory.h"

PlayerInfoConsumer::PlayerInfoConsumer() = default;

void PlayerInfoConsumer::consume(PlayerInfoPacket &packet, EnginePtr engine, RTypeServer server) {
    auto typeFactory = engine->getModule<LuaEntityTypeFactory>();
    auto lib = engine->getModule<IGraphicLib>();

    auto player = engine->getScene()->getOrCreateEntityById(packet.playerId);
    typeFactory->initEntity(player, "player");

    std::string spriteName = "player" + std::to_string(packet.playerNumber + 1);
    auto spriteProp = lib->getSpriteProperties()->getValue(spriteName);
    auto sprite = spriteProp->createSprite(spriteProp);
    int spriteId = lib->getSprites()->add(sprite);

    player->getOrCreate<SpriteComponent>(spriteId);

    std::cout << ">> We are player " << packet.playerId << " (" << packet.playerNumber << ")" << std::endl;

    auto pl = engine->registerModule<Player>();
    pl->entity = player;

    engine->getModule<IGraphicLib>()->addSystem<PlayerKeysSystem>(pl);

    engine->getScene()->addSystem<PlayerMoveSystem>(pl);
    engine->getScene()->addSystem<PlayerShootSystem>(pl);
}
