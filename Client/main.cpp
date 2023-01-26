//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "RaylibGraphicLib.h"
#include "FixTextureComponent.h"
#include "DrawFixTextureSystem.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Network/CrossPlatformSocket.h"
#include "Engine/Network/NetworkRemoteServer.h"
#include "Engine/Network/Packets/TestPacket.h"
#include "Engine/Network/Packets/EntityTestPacket.h"
#include "PingPacketConsumer.h"
#include "StayAliveSystem.h"
#include "Engine/Network/Packets/HandshakePacket.h"
#include "HandshakeResponseConsumer.h"
#include "MainMenu.h"
#include <mutex>
#include <condition_variable>

std::mutex graphicMutex;
std::condition_variable cv;
bool graphicReady = false;

bool windowClosed = false;

class tts : public PacketConsumer<TestPacket, Engine&> {
public:
    void consume(TestPacket &packet, Engine &e) override {
        std::cout << "packet received: " << packet.getValue() << std::endl;
    }
};

class EntityTestConsumer : public PacketConsumer<EntityTestPacket, Engine&> {
public:
    void consume(EntityTestPacket &packet, Engine &e) override {
        //std::cout << "EntityTest id: " << packet.entityId << "x: " << packet.x << "y: " << packet.y << std::endl;

        auto entity = e.getScene()->getEntityById(packet.entityId);
        auto pos = entity.getComponent<PositionComponent>();
        if (pos == nullptr) {
            pos = entity.addComponent<PositionComponent>();
        }
        pos->setX(packet.x);
        pos->setY(packet.y);
    }
};

void loadNetwork(Engine &e) {
    std::unique_lock<std::mutex> lck(graphicMutex);

    std::cout << "[NETWORK] waiting for graphic" << std::endl;
    while (!graphicReady) {
        cv.wait(lck);
    }
    std::cout << "[NETWORK] graphic ready" << std::endl;
    NetworkRemoteServer<Engine&> server(e, "127.0.0.1", 4242);

    server.addConsumer<EntityTestConsumer>();
    server.addConsumer<PingPacketConsumer>(server);
    server.addConsumer<HandshakeResponseConsumer>(server);

    server.addSystem<StayAliveSystem>(server);

    server.sendPacket(HandshakePacket());

    server.startListening();

    while (!windowClosed) {
        server.update(e);
        Sleep(100);
    }

    std::cout << "Graphic closed, closing network" << std::endl;
}

void graphicLoop(Engine &e) {
    std::shared_ptr<IGraphicLib> lib = e.getGraphicLib();
    IWindow &window = lib->getWindow();

    while (!window.shouldClose()) {
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