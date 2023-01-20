//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Network/NetworkServer.h"

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

class MyServer : public NetworkServer {
public:
    MyServer(const std::string &address, unsigned short port) : NetworkServer(address, port) {}

    bool clientConnected(NetworkClient &client) override {
        std::cout << "received" << std::endl;
        client.send("Hello, Client!", 14);
        client.setListener([](NetworkClient &client, char *message, int length) {
            std::cout << "lambda received: " << length << " " << message << std::endl;
            return true;
        });
        return true;
    }
};

int main()
{
    MyServer server("127.0.0.1", 4242);
    std::cout << "running" << std::endl;
    server.startListening();

    while (true) {
        Sleep(1000);
    }
    return 10;
}