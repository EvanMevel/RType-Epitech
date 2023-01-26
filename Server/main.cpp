//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Network/NetServer.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Network/Packets/TestPacket.h"
#include "Engine/Network/Packets/EntityTestPacket.h"
#include "Engine/Component/PositionComponent.h"
#include "RTypeServer.h"
#include "PingPacketConsumer.h"
#include "TimeoutSystem.h"
#include "HandshakeConsumer.h"

std::atomic<bool> running = true;

class TpEntitySystem : public ISystem {
public:
    RTypeServer &srv;
    int count = 0;

    explicit TpEntitySystem(RTypeServer &srv) : srv(srv) {}

    void update(Engine &engine) override {
        count = (count + 1) % 4;
        if (count != 0) {
            return;
        }
        for (auto &entity: engine.getScene()->getEntities()) {
            auto pos = entity.getComponent<PositionComponent>();
            if (pos != nullptr) {
                int random_number = std::rand() % 480;
                int random_number2 = std::rand() % 480;

                pos->setX(random_number);
                pos->setY(random_number2);

                EntityTestPacket packet(entity.getId(), random_number, random_number2);
                srv.broadcast(packet);
            }
        }
    }
};

void testSrv(Engine &e) {
    RTypeServer srv("127.0.0.1", 4242);
    std::cout << "running" << std::endl;

    srv.addConsumer<PingPacketConsumer>();
    srv.addConsumer<HandshakeConsumer>(srv);
    srv.addSystem<TimeoutSystem>(srv);

    std::cout << "Server listening" << std::endl;

    srv.startListening();

    e.getScene()->addSystem<TpEntitySystem>(srv);

    Entity &ent = e.getScene()->createEntity();
    ent.addComponent<PositionComponent>();

    while (running.load()) {
        auto start = std::chrono::system_clock::now();

        e.updateScene();
        srv.update(e);

        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        Sleep((1000 / 20) - elapsed.count());
    }
}

void stopThread() {
    std::cin.get();
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

    return 10;
}