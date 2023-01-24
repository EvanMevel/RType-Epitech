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

void testSrv() {
    RTypeServer srv("127.0.0.1", 4242);
    std::cout << "running" << std::endl;

    srv.addConsumer<PingPacketConsumer>();
    srv.addConsumer<HandshakeConsumer>(srv);
    srv.addSystem<TimeoutSystem>(srv);

    Engine e;
    auto sc = e.createScene<Scene>();
    e.setScene(sc);
    sc->addSystem<TpEntitySystem>(srv);

    Entity &ent = sc->createEntity();
    ent.addComponent<PositionComponent>();

    srv.startListening();
    while (true) {
        auto start = std::chrono::system_clock::now();

        e.updateScene();
        srv.update(e);

        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        Sleep((1000 / 20) - elapsed.count());
    }
}

int main()
{
    testSrv();


    return 10;
}