//
// Created by aaama on 24/01/2023.
//

#include "MainMenu.h"

std::shared_ptr<Scene> mainMenu(Engine &e)
{
    auto sc = e.createScene<Scene>();
    Entity &background = sc->createEntity();
    std::cout << "EntityId: " << background.getId() << std::endl;

    auto graph = e.getGraphicLib();
    auto texture = graph->createTexture("../Client/assets/img.png");
    background.addComponent<FixTextureComponent>()->setTexture(texture);
    auto pos = background.addComponent<PositionComponent>();
    pos->setX(0);
    pos->setY(0);

    Entity &playButton = createButton(e,sc,"../Client/assets/texture.png",25,25);
    Entity &quitButton = createButton(e,sc,"../Client/assets/texture.png",55,55);
    return sc;
}