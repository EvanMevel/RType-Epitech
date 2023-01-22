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

void testSrv() {
    MyServer srv("127.0.0.1", 4242);
    std::cout << "running" << std::endl;

    Engine e;
    auto sc = e.createScene<Scene>();
    e.setScene(sc);
    sc->addSystem<TpEntitySystem>(srv);

    Entity &ent = sc->createEntity();
    ent.addComponent<PositionComponent>();

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