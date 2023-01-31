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

std::atomic<bool> running = true;

void testSrv(Engine &e) {
    RTypeServerPtr srv = e.registerModule<RTypeServer>("127.0.0.1", 4242);
    std::cout << "running" << std::endl;

    srv->addConsumer<PingPacketConsumer>();
    srv->addConsumer<HandshakeConsumer>(e);
    srv->addConsumer<PlayerMoveConsumer>(e);
    srv->addConsumer<PlayerShootConsumer>(e);


    srv->addSystem<TimeoutSystem>();
    e.getScene()->addSystem<ServerVelocitySystem>();
    e.getScene()->addSystem<ProjectileCleanupSystem>();

    std::cout << "Server listening" << std::endl;

    srv->startListening();

    auto ent = e.getScene()->createEntity();
    entity::initEnemy(ent, 0, 0);

    auto ticker = e.registerModule<TickUtil>(20);

    while (running.load()) {
        ticker->startTick();

        e.updateScene();
        srv->update(e);

        ticker->endTickAndWait();
    }
    std::cout << "Server stopped" << std::endl;
}

void stopThread(Engine &e) {
    std::string str;

    do {
        std::cin >> str;
        if (str == "a") {
            auto ent = e.getScene()->getEntityById(100);
            auto physics = ent->getOrCreate<AccelerationPhysicComponent>();
            physics->acceleration.setX(5);
        } else if (str == "z") {
            auto ent = e.getScene()->getEntityById(100);
            auto physics = ent->getOrCreate<AccelerationPhysicComponent>();
            physics->acceleration.setX(-5);

        }
    } while (str != "q");

    std::cout << "Closing..." << std::endl;

    running = false;
}

int main()
{
    Engine e(100);
    auto sc = e.createScene<Scene>();
    e.setScene(sc);

    std::thread t = std::thread(stopThread, std::ref(e));

    testSrv(e);

    t.join();

    return 0;
}