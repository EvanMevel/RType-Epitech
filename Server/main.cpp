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
#include "Engine/Engine.h"
#include "RTypeServer.h"
#include "Engine/EntityUtils.h"
#include "Engine/TickUtil.h"
#include "Server/Consumers/PingPacketConsumer.h"
#include "TimeoutSystem.h"
#include "Server/Consumers/HandshakeConsumer.h"
#include "Engine/Component/HitboxComponent.h"
#include "Engine/Component/TeamComponent.h"
#include "ServerVelocitySystem.h"
#include "Server/Consumers/PlayerMoveConsumer.h"
#include "Server/Consumers/PlayerShootConsumer.h"
#include "ProjectileCleanupSystem.h"
#include "EnemyRandomSpawnSystem.h"
#include "EnemyShootSystem.h"
#include "ServerColliderSystem.h"
#include "PacketSendingScene.h"
#include "Levels.h"

std::atomic<bool> running = true;

void testSrv(EnginePtr engine) {
    RTypeServerPtr srv = engine->getModule<RTypeServer>();

    srv->addConsumer<PingPacketConsumer>();
    srv->addConsumer<HandshakeConsumer>(engine);
    srv->addConsumer<PlayerMoveConsumer>(engine);
    srv->addConsumer<PlayerShootConsumer>(engine);


    srv->addSystem<TimeoutSystem>();
    engine->getScene()->addSystem<ServerVelocitySystem>();
    engine->getScene()->addSystem<ProjectileCleanupSystem>();
    engine->getScene()->addSystem<EnemyRandomSpawnSystem>();
    engine->getScene()->addSystem<EnemyShootSystem>();
    engine->getScene()->addSystem<ServerColliderSystem>();

    log() << "Server listening" << std::endl;

    srv->startListening();

    auto ticker = engine->registerModule<TickUtil>(ENGINE_TPS);

    while (running.load()) {
        ticker->startTick();

        engine->updateScene(engine);
        srv->update(engine);

        ticker->endTickAndWait();
    }
    log() << "Server stopped" << std::endl;
}

void stopThread(EnginePtr engine) {
    std::string str;

    do {
        std::cin >> str;
        if (str == "a") {
            auto ent = engine->getScene()->getOrCreateEntityById(100);
            auto physics = ent->getOrCreate<PhysicComponent>();
            physics->acceleration.setX(5);
        } else if (str == "z") {
            auto ent = engine->getScene()->getOrCreateEntityById(100);
            auto physics = ent->getOrCreate<PhysicComponent>();
            physics->acceleration.setX(-5);

        }
    } while (str != "q");

    log() << "Closing..." << std::endl;

    running = false;
}

void createScene(EnginePtr engine) {
    engine->registerModule<Levels>();

    char *rtypeServerIp = std::getenv("RTYPE_SERVER_IP");
    std::string serverIp = rtypeServerIp ? rtypeServerIp : "127.0.0.1";
    char *rtypeServerPort = std::getenv("RTYPE_SERVER_PORT");
    int serverport = rtypeServerPort ? std::stoi(rtypeServerPort) : 4242;

    RTypeServerPtr srv = engine->registerModule<RTypeServer>(engine, serverIp, serverport);
    auto sc = engine->createScene<PacketSendingScene>(srv);
    engine->setScene(sc);

}

int main()
{
    std::unique_ptr<Engine> e = std::make_unique<Engine>(100);
    createScene(e);
    std::thread t = std::thread(stopThread, std::ref(e));

    testSrv(e);

    t.join();

    return 0;
}