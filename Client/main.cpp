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

void graphic() {
    Engine e;
    auto sc = e.createScene<Scene>();
    e.setScene(sc);

    std::shared_ptr<IGraphicLib> lib = std::make_shared<RaylibGraphicLib>();
    e.setGraphicLib(lib);

    lib->addSystem<DrawFixTextureSystem>();

    IWindow &window = lib->createWindow(500, 500, "teststs");

    Entity &ent = sc->createEntity();
    auto texture = lib->createTexture("../Client/assets/texture.png");
    ent.addComponent<FixTextureComponent>()->setTexture(texture);
    auto pos = ent.addComponent<PositionComponent>();
    pos->setX(100);
    pos->setY(100);

    while (!window.shouldClose()) {
        window.beginDrawing();
        window.setBackground(ColorCodes::COLOR_BLACK);
        e.updateGraphicLib();
        e.updateScene();
        window.endDrawing();
    }
}

class tts : public PacketConsumer<TestPacket> {
public:
    void consume(TestPacket &packet) override {
        std::cout << "packet received: " << packet.getValue() << std::endl;
    }
};

void testSrv() {
    NetworkRemoteServer server("127.0.0.1", 4242);

    server.addConsumer<tts>();

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
    graphic();
    return 0;
}