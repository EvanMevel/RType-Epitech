//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "RTypeServer.h"
#include "Engine/EntityUtils.h"
#include "Engine/TickUtil.h"
#include "PingPacketConsumer.h"
#include "TimeoutSystem.h"
#include "HandshakeConsumer.h"
#include "ServerVelocitySystem.h"
#include "PlayerMoveConsumer.h"
#include "PlayerShootConsumer.h"
#include "ProjectileCleanupSystem.h"
#include "EnemyRandomSpawnSystem.h"
#include "EnemyShootSystem.h"

std::atomic<bool> running = true;

void testSrv(EnginePtr engine) {
    RTypeServerPtr srv = engine->registerModule<RTypeServer>("127.0.0.1", 4242);
    std::cout << "running" << std::endl;

    srv->addConsumer<PingPacketConsumer>();
    srv->addConsumer<HandshakeConsumer>(engine);
    srv->addConsumer<PlayerMoveConsumer>(engine);
    srv->addConsumer<PlayerShootConsumer>(engine);


    srv->addSystem<TimeoutSystem>();
    engine->getScene()->addSystem<ServerVelocitySystem>();
    engine->getScene()->addSystem<ProjectileCleanupSystem>();
    engine->getScene()->addSystem<EnemyRandomSpawnSystem>();
    engine->getScene()->addSystem<EnemyShootSystem>();

    std::cout << "Server listening" << std::endl;

    srv->startListening();

    auto ticker = engine->registerModule<TickUtil>(20);

    while (running.load()) {
        ticker->startTick();

        engine->updateScene(engine);
        srv->update(engine);

        ticker->endTickAndWait();
    }
    std::cout << "Server stopped" << std::endl;
}

void stopThread(EnginePtr engine) {
    std::string str;

    do {
        std::cin >> str;
        if (str == "a") {
            auto ent = engine->getScene()->getEntityById(100);
            auto physics = ent->getOrCreate<AccelerationPhysicComponent>();
            physics->acceleration.setX(5);
        } else if (str == "z") {
            auto ent = engine->getScene()->getEntityById(100);
            auto physics = ent->getOrCreate<AccelerationPhysicComponent>();
            physics->acceleration.setX(-5);

        }
    } while (str != "q");

    std::cout << "Closing..." << std::endl;

    running = false;
}

int main()
{
    std::unique_ptr<Engine> e = std::make_unique<Engine>(100);
    auto sc = e->createScene<Scene>();
    e->setScene(sc);

    std::thread t = std::thread(stopThread, std::ref(e));

    testSrv(e);

    t.join();

    return 0;
}