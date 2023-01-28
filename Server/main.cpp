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
#include "Engine/Component/VelocityComponent.h"
#include "Engine/Component/AccelerationComponent.h"
#include "VelocitySystem.h"

std::atomic<bool> running = true;

void testSrv(Engine &e) {
    RTypeServerPtr srv = std::make_shared<RTypeServer>("127.0.0.1", 4242);
    std::cout << "running" << std::endl;

    srv->addConsumer<PingPacketConsumer>();
    srv->addConsumer<HandshakeConsumer>(srv, e);
    srv->addSystem<TimeoutSystem>(srv);
    e.getScene()->addSystem<VelocitySystem>(srv);

    std::cout << "Server listening" << std::endl;

    srv->startListening();

    auto ent = e.getScene()->createEntity();
    ent->addComponent<PositionComponent>();
    ent->addComponent<VelocityComponent>();
    ent->addComponent<AccelerationComponent>();

    auto acc = ent->getComponent<AccelerationComponent>();
    acc->setX(5);

    while (running.load()) {
        auto start = std::chrono::system_clock::now();

        e.updateScene();
        srv->update(e);

        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        Sleep((1000 / 20) - elapsed.count());
    }
}

void stopThread() {
    std::cin.get();
    std::cout << "Closing..." << std::endl;

    running = false;
}

int main()
{
    std::thread t = std::thread(stopThread);

    Engine e;
    auto sc = e.createScene<Scene>();
    e.setScene(sc);

    testSrv(e);

    t.join();

    return 0;
}