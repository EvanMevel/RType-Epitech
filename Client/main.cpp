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
#include "MainMenu.h"
#include <mutex>
#include <condition_variable>

std::mutex graphicMutex;
std::condition_variable cv;
bool graphicReady = false;

void initGraphic(Engine &e) {
    std::unique_lock<std::mutex> lck(graphicMutex);

    std::shared_ptr<IGraphicLib> lib = std::make_shared<RaylibGraphicLib>();
    e.setGraphicLib(lib);

    lib->addSystem<DrawFixTextureSystem>();

    IWindow &window = lib->createWindow(500, 500, "teststs");
    window.setTargetFPS(60);
    std::cout << "Graph ready" << std::endl;

    graphicReady = true;
    cv.notify_all();
}

void graphicLoop(Engine &e) {

    initGraphic(e);

    std::shared_ptr<IGraphicLib> lib = e.getGraphicLib();
    IWindow &window = lib->getWindow();

    while (!window.shouldClose()) {
        window.beginDrawing();
        window.setBackground(ColorCodes::COLOR_BLACK);
        e.updateGraphicLib();
        e.updateScene();
        window.endDrawing();
    }
}

class tts : public PacketConsumer<TestPacket, Engine&> {
public:
    void consume(TestPacket &packet, Engine &e) override {
        std::cout << "packet received: " << packet.getValue() << std::endl;
    }
};

class EntityTestConsumer : public PacketConsumer<EntityTestPacket, Engine&> {
public:
    void consume(EntityTestPacket &packet, Engine &e) override {
        std::cout << "EntityTest id: " << packet.entityId << "x: " << packet.x << "y: " << packet.y << std::endl;

        auto entity = e.getScene()->getEntityById(packet.entityId);
        auto pos = entity.getComponent<PositionComponent>();
        if (pos == nullptr) {
            pos = entity.addComponent<PositionComponent>();
        }
        pos->setX(packet.x);
        pos->setY(packet.y);
    }
};

void testSrv() {
    Engine e;

    //initGraphic(e);

    std::cout << "done" << std::endl;


    std::thread graph(graphicLoop, std::ref(e));

    std::unique_lock<std::mutex> lck(graphicMutex);

    while (!graphicReady) {
        cv.wait(lck);
    }
    std::cout << "apres" << std::endl;
    auto sc = mainMenu(e);
    e.setScene(sc);

    NetworkRemoteServer<Engine&> server(e, "127.0.0.1", 4242);

    server.addConsumer<tts>();
    server.addConsumer<EntityTestConsumer>();

    TestPacket packet;
    packet.setValue(42);
    server.sendPacket(packet);

    server.startListening();

    while (true) {
        Sleep(1000);
    }
}

int main()
{
    testSrv();
    return 0;
}