//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Network/NetServer.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Network/Packets/TestPacket.h"
#include "Engine/Network/Packets/EntityTestPacket.h"

class TestSystem : public ISystem {
    void update(Engine &engine) override {
        std::cout << "begin test system" << std::endl;
        for (auto &entity: engine.getScene()->getEntities()) {
            std::cout << "entity: " << entity.getId() << std::endl;
            auto type = entity.getComponent<EntityTypeComponent>();
            if (entity.hasComponent<EntityTypeComponent>()) {
                std::cout << "type: " << type->getType() << std::endl;
            }
        }
    }
};

void engine() {
    Engine e;
    auto sc = e.createScene<Scene>();
    e.setScene(sc);
    Entity &ent = sc->createPlayer();
    Entity &ent2 = sc->createEntity();
    sc->addSystem<TestSystem>();
    sc->update(e);
}

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

void testSrv() {
    MyServer srv("127.0.0.1", 4242);
    std::cout << "running" << std::endl;

    srv.addConsumer<TT>(15);

    srv.startListening();
    while (true) {
        Sleep(300);
        int random_number = std::rand() % 480;
        int random_number2 = std::rand() % 480;
        EntityTestPacket packet(0, random_number, random_number2);
        srv.broadcast(packet);
    }
}

int main()
{
    testSrv();


    return 10;
}