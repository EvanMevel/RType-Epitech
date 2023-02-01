//
// Created by aaama on 24/01/2023.
//

#include "MainMenu.h"

std::shared_ptr<Scene> mainMenu(EnginePtr engine)
{
    auto sc = engine->createScene<Scene>();
    /*auto background = sc->createEntity();
    std::cout << "EntityId: " << background->getId() << std::endl;

    auto graph = e.getEngineComponent<IGraphicLib>();
    auto texture = graph->createTexture("../Client/assets/img.png");
    background->addComponent<FixTextureComponent>()->setTexture(texture);
    auto pos = background->addComponent<PositionComponent>();
    pos->setX(0);
    pos->setY(0);

    auto playButton = createButton(e,sc,"../Client/assets/texture.png",25,25);
    auto quitButton = createButton(e,sc,"../Client/assets/texture.png",55,55);*/
    return sc;
}