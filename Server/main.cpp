//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Network/NetServer.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Network/Packets/TestPacket.h"
#include "Engine/Network/Packets/EntityTestPacket.h"
#include "Engine/Network/Packets/EntityVelocityAccelerationPositionPacket.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/VelocityComponent.h"
#include "Engine/Component/AccelerationComponent.h"
#include "Engine/Vector2i.h"

class TT : public PacketClientConsumer<TestPacket, int> {
private:
    int e;
public:
    explicit TT(int e) : e(e) {}

    void consume(TestPacket &packet, std::shared_ptr<NetClient> client, int i) override {
        std::cout << "packet received: " << packet.getValue() << " data is " << i << " and e is " << e << std::endl;
        client->sendPacket(packet);
    }
};

class MyServer : public NetServer<int> {
public:
    MyServer(const std::string &address, unsigned short port) : NetServer(address, port) {}

    int createData(std::shared_ptr<NetClient> &client) override {
        return client->getPort();
    }

    void clientConnected(std::shared_ptr<NetClient> &client, int &data) override {
        std::cout << "Client connected " << client->getAddress() << ":" << client->getPort() << std::endl;
    }
};

class TpEntitySystem : public ISystem {
public:
    MyServer &srv;
    int count = 0;

    explicit TpEntitySystem(MyServer &srv) : srv(srv) {}

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

                std::cout << "VELOCITY X : " << vel->getX() << " ACCELERATION X : " << accel->getX() << std::endl;
                int velY = vel->getY() + accel->getY();
                int velX = vel->getX() + accel->getX();

                std::cout << "velY: " << velY << " velX: " << velX << "    ";
                vel->setX(velX);
                vel->setY(velY);

                int posX = pos->getX() + vel->getX();
                int posY = pos->getY() + vel->getY();

                std::cout << "posY: " << posY << " posX: " << posX << "    ";
                pos->setX(posX);
                pos->setY(posY);

                int accelX = accel->getX();
                int accelY = accel->getY();

                std::cout << "accelY: " << accelY << " accelX: " << accelX << std::endl;

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

                EntityVelocityAccelerationPositionPacket packet(entity.getId(), Vector2i(posX, posY), Vector2i(velX, velY), Vector2i(accelX, accelY));
                srv.broadcast(packet);
            }
        }
    }
};

void testSrv() {
    MyServer srv("127.0.0.1", 4242);
    std::cout << "running" << std::endl;

    Engine e;
    auto sc = e.createScene<Scene>();
    e.setScene(sc);
//    sc->addSystem<TpEntitySystem>(srv);
    sc->addSystem<VelocitySystem>(srv);

    Entity &ent = sc->createEntity();
    ent.addComponent<PositionComponent>();
    ent.addComponent<VelocityComponent>();
    ent.addComponent<AccelerationComponent>();

    auto acc = ent.getComponent<AccelerationComponent>();
    acc->setX(5);

    std::cout << "ACCELERATION X: " << acc->getX() << std::endl;
    srv.addConsumer<TT>(15);

    srv.startListening();
    while (true) {
        auto start = std::chrono::system_clock::now();

        e.updateScene();

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