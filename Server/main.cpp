//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Network/NetServer.h"
#include "Engine/Network/Packets/TestPacket.h"
#include "Engine/Component/PositionComponent.h"
#include "RTypeServer.h"
#include "PingPacketConsumer.h"
#include "TimeoutSystem.h"
#include "HandshakeConsumer.h"
#include "Engine/Component/HitboxComponent.h"
#include "Engine/Component/TeamComponent.h"
#include "ServerVelocitySystem.h"
#include "Engine/Component/AccelerationPhysicComponent.h"
#include "Engine/TickUtil.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "PlayerMoveConsumer.h"
#include "ServerProjectileHitboxSystem.h"

std::atomic<bool> running = true;

void testSrv(Engine &e) {
    RTypeServerPtr srv = std::make_shared<RTypeServer>("127.0.0.1", 4242);
    std::cout << "running" << std::endl;

    srv->addConsumer<PingPacketConsumer>();
    srv->addConsumer<HandshakeConsumer>(srv, e);
    srv->addConsumer<PlayerMoveConsumer>(e, srv);


    srv->addSystem<TimeoutSystem>(srv);
    e.getScene()->addSystem<ServerVelocitySystem>(srv);
    e.getScene()->addSystem<ServerProjectileHitboxSystem>(srv);

    std::cout << "Server listening" << std::endl;

    srv->startListening();

    auto ent = e.getScene()->createEntity();
    ent->addComponent<PositionComponent>();
    ent->addComponent<EntityTypeComponent>()->setType(EntityType::ENEMY);
    ent->addComponent<AccelerationPhysicComponent>();
    ent->addComponent<HitboxComponent>();
    ent->addComponent<TeamComponent>();

    auto team = ent->getComponent<TeamComponent>();
    team->setTeam(1);

    auto hitbox = ent->getComponent<HitboxComponent>();
    hitbox->setLengthX(55);
    hitbox->setLengthY(55);

    ent = e.getScene()->createEntity();
    ent->addComponent<PositionComponent>()->setX(32);
    ent->addComponent<EntityTypeComponent>()->setType(EntityType::PROJECTILE);
    ent->addComponent<AccelerationPhysicComponent>();

    auto ticker = e.registerEngineComponent<TickUtil>(20);

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