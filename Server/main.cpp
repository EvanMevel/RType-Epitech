//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Network/PacketNetworkServer.h"
#include "Engine/Network/Packets/TestPacket.h"
#include "Engine/Network/Packets/PacketConsumer.h"

class TestSystem : public ISystem {
    void update(Engine &engine) override {
        std::cout << "begin test system" << std::endl;
        for (auto &entity: engine.getScene()->getEntities()) {
            std::cout << "entity: " << entity.getId() << std::endl;
            auto *type = entity.getComponent<EntityTypeComponent>();
            if (entity.hasComponent<EntityTypeComponent>()) {
                std::cout << "type: " << type->getType() << std::endl;
            }
        }
    }
};

void engine() {
    Engine e;
    Scene *sc = e.createScene();
    e.setScene(sc);
    Entity &ent = sc->createPlayer();
    Entity &ent2 = sc->createEntity();
    sc->addSystem(new TestSystem());
    sc->update(e);
}

class tts : public PacketConsumer<TestPacket> {
private:
    PacketNetworkClient &client;
public:
    explicit tts(PacketNetworkClient &client) : client(client) {}
    void consume(TestPacket &packet) override {
        std::cout << "packet received: " << packet.getValue() << std::endl;
        client.sendPacket(packet);
    }
};

class MyServer : public PacketNetworkServer {
public:
    MyServer(const std::string &address, unsigned short port) : PacketNetworkServer(address, port) {}

    bool clientConnected(PacketNetworkClient &client) override {
        std::cout << "client connected" << std::endl;
        client.getConsumers().addConsumer<tts>(client);
        return true;
    }
};

void stv() {
    MyServer server("127.0.0.1", 4242);
    std::cout << "running" << std::endl;
    server.startListening();

    while (true) {
        Sleep(1000);
    }
}

int main()
{
    stv();


    return 10;
}