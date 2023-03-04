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
    std::cout << "sent packet" << std::endl;

    // Send Entity info to all clients
    std::shared_ptr<std::vector<EntityInfoPacket>> packetList = std::make_shared<std::vector<EntityInfoPacket>>();
    EnginePtr engine = e;

    std::function<void(std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> &data)> func = [&engine, &packetList](std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> &data) {
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
        sendEntitiesInfo(client, engine->getScene());

        // Send new player info to all other clients
        EntityInfoPacket newPlayerInfo(player);
        packetList->push_back(newPlayerInfo);
    };

    server->forEachClient(func);
    auto it = packetList->begin();
    while (it != packetList->end()) {
        server->broadcast(*it, client);
        it++;
    }

}
