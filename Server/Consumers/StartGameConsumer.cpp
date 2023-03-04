//
// Created by gugue on 04/03/2023.
//

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

bool StartGameConsumer::gameStarted = false;

StartGameConsumer::StartGameConsumer(EnginePtr e) : RTypePacketConsumer(e) {}

static void sendEntitiesInfo(const std::shared_ptr<NetClient>& client, std::shared_ptr<Scene> scene) {
    std::function<void(std::shared_ptr<Entity>)> sendEntityInfo = [&client](std::shared_ptr<Entity> entity) {
        auto pos = entity->getComponent<PositionComponent>();
        auto type = entity->getComponent<EntityTypeComponent2>();
        if (pos && type) {
            EntityInfoPacket packet(entity, type, pos);
            client->sendPacket(packet);
        }
    };
    scene->forEachEntity(sendEntityInfo);
}

void StartGameConsumer::consume(StartGamePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) {

    StartGameConsumer::gameStarted = true;
    // Create Scene
    auto server = e->getModule<RTypeServer>();
    auto sc = e->createScene<PacketSendingScene>(server);
    auto level = e->getModule<LuaLevelFactory>()->getLevels()[0];

    sc->addSystem<ServerVelocitySystem>();
    sc->addSystem<ProjectileCleanupSystem>();
    sc->addSystem<EnemyShootSystem>();
    sc->addSystem<ColliderHitboxSystem>();
    sc->addSystem<LevelSystem>(level);

    e->setScene(sc);

    // Send Packet to all clients
    StartGamePacket startGame;
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
        player->addComponent<PlayerInfoComponent>(playerNumber);
        data->playerNumber = playerNumber;

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
