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

void graphic() {
    Engine e;
    Scene *sc = e.createScene();
    e.setScene(sc);

    auto *lib = new RaylibGraphicLib();
    e.setGraphicLib(lib);

    auto *drawFixTextureSystem = new DrawFixTextureSystem();
    lib->addSystem(drawFixTextureSystem);

    IWindow &window = lib->createWindow(500, 500, "teststs");

    Entity &ent = sc->createEntity();
    auto texture = lib->createTexture("../Client/assets/texture.png");
    ent.addComponent<FixTextureComponent>()->setTexture(texture);
    auto *pos = ent.addComponent<PositionComponent>();
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

int main()
{
    CrossPlatformSocket socket;
    if (!socket.create()) {
        std::cout << "Failed to create socket" << std::endl;
        return 1;
    }
    const char* message = "Hello, Server!";
    int message_len = strlen(message);
    char buffer[4096];
    std::string address;
    unsigned short port;

    // Send the message to the server
    int resp = socket.sendTo(message, message_len, "127.0.0.1", 4242);
    std::cout << "resp: " << resp << std::endl;

    if (resp != message_len) {
        std::cout << "Failed to send message" << std::endl;
        return 1;
    }
    return 0;
}