//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Graphic/IGraphicLib.h"
#include "RaylibGraphicLib.h"
#include "FixTextureComponent.h"
#include "DrawFixTextureSystem.h"
#include "Engine/Component/PositionComponent.h"

int main()
{
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