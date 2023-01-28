//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "ClientNetServer.h"
#include "RaylibGraphicLib.h"
#include "DrawFixTextureSystem.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/VelocityComponent.h"
#include "Engine/Component/AccelerationComponent.h"
#include "Engine/Network/Packets/TestPacket.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Client/Consumers/PingPacketConsumer.h"
#include "StayAliveSystem.h"
#include "Engine/Network/Packets/HandshakePacket.h"
#include "Client/Consumers/HandshakeResponseConsumer.h"
#include "Consumers/PlayerInfoConsumer.h"
#include "MainMenu.h"
#include <mutex>
#include <condition_variable>

std::mutex graphicMutex;
std::condition_variable cv;
bool graphicReady = false;

std::condition_variable cv2;
bool registeredConsumers = false;

bool windowClosed = false;

class EntityVelocityPacketConsumer : public PacketConsumer<EntityVelocityPacket, Engine&> {
public:
    void consume(EntityVelocityPacket &packet, Engine &e) override {

        auto entity = e.getScene()->getEntityById(packet.entityId);
        auto pos = entity->getOrCreate<PositionComponent>();
        auto vel = entity->getOrCreate<VelocityComponent>();
        auto accel = entity->getOrCreate<AccelerationComponent>();

        pos->setX(packet.pos.x);
        pos->setY(packet.pos.y);

        vel->setX(packet.velocity.x);
        vel->setY(packet.velocity.y);

        accel->setX(packet.acceleration.x);
        accel->setY(packet.acceleration.y);
    }
};

void loadNetwork(Engine &e) {
    std::unique_lock<std::mutex> lck(graphicMutex);

    std::cout << "[NETWORK] waiting for graphic" << std::endl;
    while (!graphicReady) {
        cv.wait(lck);
    }
    std::cout << "[NETWORK] graphic ready" << std::endl;
    RTypeServer server = std::make_shared<NetworkRemoteServer<Engine&>>(e, "127.0.0.1", 4242);

    server->addConsumer<EntityVelocityPacketConsumer>();
    server->addConsumer<PingPacketConsumer>(server);
    server->addConsumer<HandshakeResponseConsumer>(server);


    std::function<void(std::shared_ptr<IGraphicLib>, RTypeServer server)> fu = [](std::shared_ptr<IGraphicLib> lib, RTypeServer server) {

        std::cout << "Registering server consumer on graphic thread..." << std::endl;
        server->addConsumer<PlayerInfoConsumer>(lib->createTexture("../Client/assets/player.png"));

        registeredConsumers = true;
        cv2.notify_all();
    };

    e.getGraphicLib()->execOnLibThread(fu, e.getGraphicLib(), server);

    server->addSystem<StayAliveSystem>(server);

    std::cout << "Waiting for consumer register on graphicLib thread" << std::endl;

    while (!registeredConsumers) {
        cv2.wait(lck);
    }

    std::cout << "Sending handshake" << std::endl;

    server->startListening();

    server->sendPacket(HandshakePacket());


    while (!windowClosed) {
        server->update(e);
        Sleep(100);
    }

    std::cout << "Graphic closed, closing network" << std::endl;
}

void graphicLoop(Engine &e) {
    std::shared_ptr<IGraphicLib> lib = e.getGraphicLib();
    IWindow &window = lib->getWindow();

    while (!window.shouldClose()) {
        auto it = lib->getExecs().begin();
        while (it != lib->getExecs().end()) {
            (*it)();
            it = lib->getExecs().erase(it);
        }
        if (window.shouldClose()) {
            break;
        }
        window.beginDrawing();
        window.setBackground(ColorCodes::COLOR_BLACK);
        e.updateGraphicLib();
        e.updateScene();
        window.endDrawing();
    }
    windowClosed = true;
}

void loadScenes(Engine &e) {
    auto sc = mainMenu(e);
    e.setScene(sc);
}

void loadGraphsAndScenes(Engine &e) {
    std::unique_lock<std::mutex> lck(graphicMutex);

    std::cout << "[Graphic] Starting..." << std::endl;

    std::shared_ptr<IGraphicLib> lib = std::make_shared<RaylibGraphicLib>();
    e.setGraphicLib(lib);

    lib->addSystem<DrawFixTextureSystem>();

    IWindow &window = lib->createWindow(500, 500, "teststs");
    window.setTargetFPS(60);
    std::cout << "[Graphic] Window created" << std::endl;

    loadScenes(e);
    std::cout << "[Graphic] Scenes ready" << std::endl;

    graphicReady = true;
    cv.notify_all();

    std::cout << "[Graphic] Finished loading" << std::endl;

    lck.unlock();
}

void startGraph(Engine &e) {
    loadGraphsAndScenes(e);
    graphicLoop(e);
}

void loadAll() {
    Engine e;

    std::thread net(startGraph, std::ref(e));

    loadNetwork(e);

    net.join();
}

int main()
{
    loadAll();

    return 0;
}