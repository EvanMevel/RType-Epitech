//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Network/NetServer.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Network/Packets/TestPacket.h"
#include "Engine/Network/Packets/EntityTestPacket.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Engine/Component/PositionComponent.h"
#include "RTypeServer.h"
#include "PingPacketConsumer.h"
#include "TimeoutSystem.h"
#include "HandshakeConsumer.h"
#include "Engine/Component/VelocityComponent.h"
#include "Engine/Component/AccelerationComponent.h"
#include "Engine/Vector2i.h"

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

class VelocitySystem : public ISystem {
public:
    MyServer &srv;
    int count = 0;

    explicit VelocitySystem(MyServer &srv) : srv(srv) {}

    void update(Engine &engine) override {
        count = (count + 1) % 4;
        if (count != 0) {
            return;
        }
        for (auto &entity: engine.getScene()->getEntities()) {
            auto pos = entity.getComponent<PositionComponent>();
            auto vel = entity.getComponent<VelocityComponent>();
            auto accel = entity.getComponent<AccelerationComponent>();
            if (pos != nullptr && vel != nullptr && accel != nullptr) {

                int velY = vel->getY() + accel->getY();
                int velX = vel->getX() + accel->getX();

                vel->setX(velX);
                vel->setY(velY);

                int posX = pos->getX() + vel->getX();
                int posY = pos->getY() + vel->getY();

                pos->setX(posX);
                pos->setY(posY);

                int accelX = accel->getX();
                int accelY = accel->getY();

                if (accelX < 0)
                    accel->setX(accelX + 1);
                else if (accelX > 0)
                    accel->setX(accelX - 1);
                else
                    accel->setX(0);

                if (accelY < 0)
                    accel->setY(accelY + 1);
                else if (accelY > 0)
                    accel->setY(accelY - 1);
                else
                    accel->setY(0);

                if (velX < 0)
                    vel->setX(velX + 1);
                else if (velX > 0)
                    vel->setX(velX - 1);
                else
                    vel->setX(0);

                if (velY < 0)
                    vel->setY(velY + 1);
                else if (velY > 0)
                    vel->setY(velY - 1);
                else
                    vel->setY(0);

                EntityVelocityPacket packet(entity.getId(), Vector2i(posX, posY), Vector2i(velX, velY), Vector2i(accelX, accelY));
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
    e.getScene()->addSystem<VelocitySystem>(srv);

    std::cout << "Server listening" << std::endl;

    srv.startListening();

    //e.getScene()->addSystem<TpEntitySystem>(srv);

    Entity &ent = e.getScene()->createEntity();
    ent.addComponent<PositionComponent>();
    ent.addComponent<VelocityComponent>();
    ent.addComponent<AccelerationComponent>();

    auto acc = ent.getComponent<AccelerationComponent>();
    acc->setX(5);

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

    return 0;
}