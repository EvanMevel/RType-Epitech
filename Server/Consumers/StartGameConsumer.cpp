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

#include "StartGameConsumer.h"
#include "Engine/engineLua/LuaEntityTypeFactory.h"
#include "Engine/Component/PositionComponent.h"
#include "Server/PlayerList.h"
#include "Engine/Component/PlayerInfoComponent.h"
#include "Engine/Network/Packets/PlayerInfoPacket.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"
#include "Engine/Engine.h"
#include "Server/PacketSendingScene.h"
#include "Engine/Network/Packets/StartGamePacket.h"
#include "Server/ProjectileCleanupSystem.h"
#include "Server/ServerVelocitySystem.h"
#include "Server/EnemyShootSystem.h"
#include "Engine/ColliderHitboxSystem.h"
#include "Server/LevelSystem.h"
#include "Engine/engineLua/LuaLevelFactory.h"
#include "Server/BossSystem.h"

bool StartGameConsumer::gameStarted = false;

StartGameConsumer::StartGameConsumer(EnginePtr e) : RTypePacketConsumer(e) {}

static void sendEntitiesInfo(const std::shared_ptr<NetClient>& client, std::shared_ptr<Scene> scene) {
    std::function<void(std::shared_ptr<Entity>)> sendEntityInfo = [&client](std::shared_ptr<Entity> entity) {
        auto pos = entity->getComponent<PositionComponent>();
        auto type = entity->getComponent<EntityTypeComponent>();
        if (pos && type) {
            EntityInfoPacket packet(entity, type, pos);
            client->sendPacket(packet);
        }
    };
    scene->forEachEntity(sendEntityInfo);
}

void StartGameConsumer::consume(StartGamePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) {
    if (StartGameConsumer::gameStarted) {
        return;
    }
    StartGameConsumer::gameStarted = true;

    // Create Scene
    auto server = e->getModule<RTypeServer>();
    auto sc = e->createScene<PacketSendingScene>(server);
    auto level = e->getModule<LuaLevelFactory>();

    for (int i = 0; i < level->getLevels().size(); i++) {
        if (level->getLevels()[i]->getName() == packet.levelName) {
            level->setSelectedLevel(i);
            break;
        }
    }

    sc->addSystem<ServerVelocitySystem>();
    sc->addSystem<ProjectileCleanupSystem>();
    sc->addSystem<EnemyShootSystem>();
    sc->addSystem<ColliderHitboxSystem>();
    sc->addSystem<LevelSystem>(level->getLevels()[level->getSelectedLevel()]);
    sc->addSystem<BossSystem>();

    e->setScene(sc);

    // Send Packet to all clients
    StartGamePacket startGame(level->getLevels()[level->getSelectedLevel()]->getName());
    server->broadcast(startGame);

    // Send Entity info to all clients
    EnginePtr engine = e;

    std::function<void(std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> &data)> func = [&engine](std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> &data) {
        // Init player
        auto typeFactory = engine->getModule<LuaEntityTypeFactory>();
        auto player = engine->getScene()->createEntity();
        typeFactory->initEntity(player, "player");
        player->addComponent<PositionComponent>(100, 100);

        data->playerId = player->getId();
        auto playerList = engine->getModule<PlayerList>();
        int playerNumber = playerList->getAvailable();
        data->playerNumber = playerNumber;

        player->addComponent<PlayerInfoComponent>(playerNumber);

        // Send player info to client then send all entities to client
        PlayerInfoPacket playerInfo(player);
        client->sendPacket(playerInfo);
    };

    server->forEachClient(func);
    std::function<void(std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> &data)> func2 = [&engine](std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> &data) {
        sendEntitiesInfo(client, engine->getScene());
    };
    server->forEachClient(func2);
}
